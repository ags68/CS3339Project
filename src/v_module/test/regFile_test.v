module regfile_test;

reg [4:0] rd_reg_A, rd_reg_B, wr_reg;
reg [31:0] din;
reg clk, regWrite;
wire [31:0] dout_A, dout_B;

reg [5:0] indexA, indexB;
reg [31:0] randomData [0:31];
wire [1023:0] regOut;

reg fail;

regfile dut(
  rd_reg_A, rd_reg_B,
  wr_reg,
  din,
  dout_A, dout_B,
  clk, regWrite,
  regOut
);

initial begin
    $display("Testing Verilog Register File...");
    clk = 0;
    regWrite = 1;
    fail = 0;

    // Fill register file and check that you can read out a value on the same cycle it is written.
    for (indexA = 0; indexA < 32 && !fail; indexA = indexA +1) begin
        randomData[indexA] = $random;
        din = randomData[indexA];
        wr_reg = indexA[4:0];
        rd_reg_A = wr_reg;
        rd_reg_B = wr_reg;
        clk = 1;
        #10
        clk = 0;
        #1
        if (dout_A !== din) begin
            $display("Reg File FAILURE: din (0x%04x) and dout_A (0x%04x) not equal when register $%02d written and read on same cycle", din, dout_A, wr_reg);
            fail = 1;
        end
        if (dout_B !== din) begin
            $display("Reg File FAILURE: din (0x%04x) and dout_B (0x%04x) not equal when register $%02d written and read on same cycle", din, dout_B, wr_reg);
            fail = 1;
        end
        #9;
    end

    // Stop writing and make sure you can read back all data with all combinations of rd_reg
    regWrite = 0;
    for (indexA = 0; indexA < 32 && !fail; indexA = indexA +1) begin
        for (indexB = 0; indexB < 32 && !fail; indexB = indexB +1) begin
            rd_reg_A = indexA[4:0];
            rd_reg_B = indexB[4:0];
            clk = 1;
            #10
            clk = 0;
            if (dout_A !== randomData[rd_reg_A]) begin
                $display("Reg File FAILURE: dout_A (0x%08x) does not equal dout_A_exp (0x%08x) when read from register $%02d", dout_A, randomData[rd_reg_A], rd_reg_A);
                fail = 1;
            end
            if (dout_B !== randomData[rd_reg_B]) begin
                $display("Reg File FAILURE: dout_B (0x%08x) does not equal dout_B_exp (0x%08x) when read from register $%02d", dout_B, randomData[rd_reg_B], rd_reg_B);
                fail = 1;
            end
            #10;
        end
    end
end

endmodule
