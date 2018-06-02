module processor_tb();

parameter tck = 10; ///< clock tick

reg clk, load;
reg [31:0] configParams [0:5];
reg [31:0] inst, instAddr, randVal1, randVal2, randVal3;
integer DATA_DEP, BRANCH_FREQ, NUM_INSTR, NUM_CYCLE, SEED, PRINTCYCLE;
integer instNum, cycles, instType, param, tempParam, power, file;
integer regNumber, verbose = 0;

reg [31:0] vRegs [0:31];
reg [31:0] cRegs [0:31];

wire [1023:0] vreg, cppreg;

cpp_processor cpp_dut(clk, inst, instAddr, load, cppreg);
processor v_dut(clk, inst, instAddr, load, vreg);

always #(tck/2) clk <= ~clk; // clocking device

initial begin
   $dumpfile("processor_tb.vcd");
   $dumpvars(0, processor_tb);
end

initial begin
    $readmemh("configuration.hex", configParams);
    for(param = 0; param < 6; param = param + 1) begin
        tempParam = 0;
        for(power = 0; power < 8; power = power + 1) begin
            tempParam = tempParam + configParams[param]%16 * 10 ** power;
            configParams[param] = configParams[param] >> 4;
        end
        configParams[param] = tempParam;
    end
    SEED = configParams[0];
    DATA_DEP = configParams[1];
    BRANCH_FREQ = configParams[2];
    NUM_INSTR = configParams[3];
    NUM_CYCLE = configParams[4];
    PRINTCYCLE = configParams[5];
    $display("CONFIGURATION VALUES:\n");
    $display("Seed for random number generation:\t%d",SEED);
    $display("Data dependency:\t\t\t%d", DATA_DEP);
    $display("Branch Frequency:\t\t\t%d", BRANCH_FREQ);
    $display("Number of instructions:\t\t\t%d", NUM_INSTR);
    $display("Number of cycles:\t\t\t%d", NUM_CYCLE);
    load = 1;
    cycles = 0;
    inst = 0;
    clk = 0;
    // Generating and loading random instructions
    $display("\nGenerating and loading random instructions...");
    file = $fopen("instructions.out", "w");
    for (instNum = 0; instNum < NUM_INSTR - 1; instNum = instNum + 1) begin
        instAddr = instNum * 4;
        if(verbose) $display(instAddr);
        instType = $urandom(SEED)%100;
        if (instType < BRANCH_FREQ) begin
            case($urandom(SEED)%4)
                0: begin
                    // Limit target to addresses that will have instructions.
                    randVal1 = ($urandom(SEED)%NUM_INSTR);
                    inst = {6'b000010,randVal1[25:0]};
                    $fwrite(file, "%d: jump %d\n", instAddr, randVal1[25:0]);
                    if(verbose) $display("jump %d", randVal1[25:0]);
                    if(verbose) $display("%032b", inst);
                end
                1: begin
                    randVal1 = ($urandom(SEED)%NUM_INSTR);
                    inst = {6'b000011,randVal1[25:0]};
                    $fwrite(file, "%d: jal %d\n", instAddr, randVal1[25:0]);
                    if(verbose) $display("jal %d", randVal1[25:0]);
                    if(verbose) $display("%032b", inst);
                end
                2: begin
                    // Only jump register to $31 ($ra)
                    // Don't ever write to $31 (except in jal) to ensure it is valid instr address.
                    inst = {6'b000000,5'b11111,{15{1'b0}},6'b001000};
                    $fwrite(file, "%d: jr $%d\n", instAddr, 5'b11111);
                    if(verbose) $display("jr $%d", 5'b11111);
                    if(verbose) $display("%032b", inst);
                end
                3: begin
                    randVal1 = $urandom(SEED)%32;
                    randVal2 = $urandom(SEED)%32;
                    if (NUM_INSTR - instNum > 132) begin
                        randVal3 = $urandom(SEED)%128;
                    end
                    else begin
                        randVal3 = $urandom(SEED)%(NUM_INSTR - instNum);
                    end
                    // Should branch offset be limited to stay within generated addresses?
                    inst = {6'b000100,randVal1[4:0],randVal2[4:0],randVal3[15:0]};
                    $fwrite(file, "%d: beq $%d, $%d, %d\n", instAddr, randVal1[4:0], randVal2[4:0], randVal3[15:0]);
                    if(verbose) $display("beq $%d, $%d, %d", randVal1[4:0], randVal2[4:0], randVal3[15:0]);
                    if(verbose) $display("%032b", inst);
                end
            endcase
        end
        else if (instType < BRANCH_FREQ + DATA_DEP) begin
            if ($urandom(SEED)%2) begin
                randVal1 = $urandom(SEED)%30 + 1; // Don't write to $0 or $31
                // Keep data address between last instruction and end of memory.
                randVal3 = $urandom_range(511,NUM_INSTR)*4;
                inst = {6'b100011,5'b0,randVal1[4:0],randVal3[15:0]};
                $fwrite(file, "%d: lw $%d, %d($%d)\n", instAddr, randVal1[4:0], randVal3[15:0], 5'b0);
                if(verbose) $display("lw $%d, %d($%d)",randVal1[4:0], randVal3[15:0], 5'b0);
                if(verbose) $display("%032b", inst);
            end
            else begin
                randVal1 = $urandom(SEED)%32;
                // Keep data address between last instruction and end of memory.
                randVal3 = $urandom_range(511,NUM_INSTR)*4;
                inst = {6'b101011,5'b0,randVal1[4:0],randVal3[15:0]};
                $fwrite(file, "%d: sw $%d, %d($%d)\n", instAddr, randVal1[4:0], randVal3[15:0], 5'b0);
                if(verbose) $display("sw $%d, %d($%d)",randVal1[4:0], randVal3[15:0], 5'b0);
                if(verbose) $display("%032b", inst);
            end
        end
        else begin
            case($urandom(SEED)%5)
                0: begin
                    randVal1 = $urandom(SEED)%32;
                    randVal2 = $urandom(SEED)%30 + 1; // Don't write to $0 or $31
                    randVal3 = $urandom(SEED);
                    inst = {6'b001000,randVal1[4:0],randVal2[4:0],randVal3[15:0]};
                    $fwrite(file, "%d: addi $%d, $%d, %d\n",instAddr,randVal2[4:0],randVal1[4:0],randVal3[15:0]);
                    if(verbose) $display("addi $%d, $%d, %d",randVal2[4:0],randVal1[4:0],randVal3[15:0]);
                    if(verbose) $display("%032b", inst);
                end
                1: begin
                    randVal1 = $urandom(SEED)%32;
                    randVal2 = $urandom(SEED)%30 + 1; // Don't write to $0 or $31
                    randVal3 = $urandom(SEED);
                    inst = {6'b001010,randVal1[4:0],randVal2[4:0],randVal3[15:0]};
                    $fwrite(file, "%d: subi $%d, $%d, %d\n",instAddr,randVal2[4:0],randVal1[4:0],randVal3[15:0]);
                    if(verbose) $display("subi $%d, $%d, %d",randVal2[4:0],randVal1[4:0],randVal3[15:0]);
                    if(verbose) $display("%032b", inst);
                end
                2: begin
                    randVal1 = $urandom(SEED)%32;
                    randVal2 = $urandom(SEED)%32;
                    randVal3 = $urandom(SEED)%30 + 1; // Don't write to $0 or $31
                    inst = {6'b000000,randVal1[4:0],randVal2[4:0],randVal3[4:0],{5{1'b0}},6'b100000};
                    $fwrite(file, "%d: add $%d, $%d, $%d\n",instAddr,randVal3[4:0],randVal1[4:0],randVal2[4:0]);
                    if(verbose) $display("add $%d, $%d, $%d",randVal3[4:0],randVal1[4:0],randVal2[4:0]);
                    if(verbose) $display("%032b", inst);
                end
                3: begin
                    randVal1 = $urandom(SEED)%32;
                    randVal2 = $urandom(SEED)%32;
                    randVal3 = $urandom(SEED)%30 + 1; // Don't write to $0 or $31
                    inst = {6'b000000,randVal1[4:0],randVal2[4:0],randVal3[4:0],{5{1'b0}},6'b100010};
                    $fwrite(file, "%d: sub $%d, $%d, $%d\n",instAddr,randVal3[4:0],randVal1[4:0],randVal2[4:0]);
                    if(verbose) $display("sub $%d, $%d, $%d",randVal3[4:0],randVal1[4:0],randVal2[4:0]);
                    if(verbose) $display("%032b", inst);
                end
                4: begin
                    randVal1 = $urandom(SEED)%32;
                    randVal2 = $urandom(SEED)%32;
                    randVal3 = $urandom(SEED)%30 + 1; // Don't write to $0 or $31
                    inst = {6'b000000,randVal1[4:0],randVal2[4:0],randVal3[4:0],{5{1'b0}},6'b100110};
                    $fwrite(file, "%d: xor $%d, $%d, $%d\n",instAddr,randVal3[4:0],randVal1[4:0],randVal2[4:0]);
                    if(verbose) $display("xor $%d, $%d, $%d",randVal3[4:0],randVal1[4:0],randVal2[4:0]);
                    if(verbose) $display("%032b", inst);
                end
            endcase
        end
        #(tck);
    end

    // Set last instruction to jump back to address 0.
    instAddr = instAddr + 4;
    randVal1 = 0;
    inst = {6'b000010,randVal1[25:0]};
    $fwrite(file, "%d: jump %d", instAddr, 25'b0);
    #(tck);
    $fclose(file);

    $display("\nGenerating and loading random data...");
    file = $fopen("data.out", "w");
    for (instNum = NUM_INSTR; instNum < 512; instNum = instNum + 1) begin
        instAddr = instNum * 4;
        inst = $urandom(SEED);
        if(verbose) $display("Loading %d in address %d", inst, instAddr);
        $fwrite(file, "%d: %x\n", instAddr, inst);
        #(tck);
    end
    $fclose(file);
    load = 0;
    $display("\nExecuting...");
end

integer mismatch = 0;
always @(posedge clk) begin
    if(!load) begin
        cycles = cycles + 1;
        #(tck/2);
        for (regNumber = 0; regNumber < 32; regNumber = regNumber +1) begin
            if (vreg[1023 - regNumber*32-:32] !== cppreg[1023 - regNumber*32-:32]) begin
                $display("Register $%d difference on cycle %d. VData = %8x CData = %8x", regNumber, cycles, vreg[1023 - regNumber*32-:32], cppreg[1023 - regNumber*32-:32]);
                mismatch = 1;
            end
            else if(verbose) $display("Register $%d match on cycle %d. VData = %8x CData = %8x", regNumber, cycles, vreg[1023 - regNumber*32-:32], cppreg[1023 - regNumber*32-:32]);
        end
        if (cycles == PRINTCYCLE) begin
            $display("\nFor cycle %0d:",cycles);
            $display("reg#\tVerilog \tC++");
            for (regNumber = 0; regNumber < 32; regNumber = regNumber +1) begin
                $display("$%0d\t%8x\t%8x", regNumber, vreg[1023 - regNumber*32-:32], cppreg[1023 - regNumber*32-:32]);
            end
        end
    end
    if(cycles >= NUM_CYCLE) begin
        if(!mismatch) $display("\nNo register mismatches detected in %0d cycles!", cycles);
        $finish;
    end
end

endmodule