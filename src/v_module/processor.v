module processor(
  clk, instToLoad, addrToLoad, load, regOut
);

input clk, load;
input [31:0] instToLoad, addrToLoad;
output [1023:0] regOut;

//////////////////////////
// Interstage registers //
//////////////////////////

// IF/ID registers
reg [31:0] IF_ID_PC;
reg [5:0] IF_ID_opCode, IF_ID_funct;
reg [4:0] IF_ID_registerRs, IF_ID_registerRt, IF_ID_registerRd, IF_ID_shamt;
reg [15:0] IF_ID_imm;
reg [25:0] IF_ID_addr;

// ID/EX registers
reg [31:0] ID_EX_readData1, ID_EX_readData2, ID_EX_imm, ID_EX_PC;
reg [1:0] ID_EX_regDst, ID_EX_aluOp, ID_EX_memtoReg;
reg ID_EX_regWrite, ID_EX_memRead, ID_EX_memWrite, ID_EX_aluSrc;
reg [5:0] ID_EX_funct;
reg [4:0] ID_EX_registerRs, ID_EX_registerRt, ID_EX_registerRd, ID_EX_shamt;

// EX/MEM registers
reg [31:0] EX_MEM_aluResult, EX_MEM_readData2, EX_MEM_PC;
reg [1:0] EX_MEM_memtoReg;
reg EX_MEM_regWrite, EX_MEM_memRead, EX_MEM_memWrite, EX_MEM_zero;
reg [4:0] EX_MEM_registerRd;

// MEM/WB registers
reg [31:0] MEM_WB_aluResult, MEM_WB_readData, MEM_WB_PC;
reg [1:0] MEM_WB_memtoReg;
reg MEM_WB_regWrite;
reg [4:0] MEM_WB_registerRd;

//////////////////////
// Interstage wires //
//////////////////////

// Control signals from ID stage to IF stage
wire PCSrc, PCWrite, IF_IDWrite, IFFlush;
wire [31:0] targetAddr;

// Data wire from WB stage to EX stage
wire [31:0] WBData;


// Instantiate modules used by multiple stages here

wire [31:0] memDataAddr, memDin, instAddr, memDout, instOut;
wire memDataRd, memDataWr;

memory memUnit(memDataAddr, memDataRd, memDataWr, memDin,
               instAddr, clk, memDout, instOut);

wire [4:0] regRdA, regRdB, regWr;
wire [31:0] regDin, regDoutA, regDoutB;
wire regWrite;

regfile registerFile(regRdA, regRdB, regWr,
                     regDin, regDoutA, regDoutB,
                     clk, regWrite, regOut);

// Use this block to stall execution to load instructions.
always @(posedge clk) begin

end

//////////////
// IF STAGE //
//////////////

//Instantiate modules used only by this stage here
reg [31:0] programCounter;

wire [31:0] IF_muxResult, programCounterPlusFour;

//Start the Program Counter at the first address
initial 
begin 
    programCounter <= 0;
end

assign programCounterPlusFour = programCounter + 4'b0100;
assign instAddr = programCounter;

Mux2to1 determineNextInstruction(IF_muxResult,programCounterPlusFour,targetAddr,PCSrc);

// Implement IF stage logic in this block
always @(posedge clk)
begin
    // Don't write PC while instructions are being loaded
    if(PCWrite == 1 && !load)
    begin
        //Set Program Counter to the Mux result if we are able to write to it
        programCounter <= IF_muxResult;
    end

    //Check to see if the values in the IF_ID Register should be udpated and there's no flush to occur
    if(IF_IDWrite == 1 && !IFFlush && !load)
    begin
        //Write instruction values to the IF_ID Register
        IF_ID_PC <= programCounterPlusFour;
        IF_ID_opCode <= instOut[31:26];

        IF_ID_registerRs <= instOut[25:21];
        IF_ID_registerRt <= instOut[20:16];
        IF_ID_registerRd <= instOut[15:11];
        IF_ID_shamt <= instOut[10:6];

        IF_ID_funct  <= instOut[5:0];

        IF_ID_imm  <= instOut[15:0];
        IF_ID_addr <= instOut[25:0];
    end
        //Only check to see if the Flush occured, and set all IF_Registers to 0 if so; 
        //if it did not, the IF_ID register states will stay the same because it's a stall
        // Flush IF/ID regsiter while loading instructions into memory.
        else if ((IF_IDWrite == 1 && IFFlush) || load)
        begin

            IF_ID_PC <= 0;
            IF_ID_opCode <= 0;
            IF_ID_registerRs <= 0;
            IF_ID_registerRt <= 0;
            IF_ID_registerRd <= 0;
            IF_ID_shamt <= 0;

            IF_ID_funct  <= 0;

            IF_ID_imm <= 0;
            IF_ID_addr <= 0;
        end
end

//////////////
// ID STAGE //
//////////////

// Connect opCode from IF/ID register to ctlUnit input
// create wires for all ctlUnit outputs
wire id_aluSrc, id_regWrite, id_memRead, id_memWrite, branch, jump;
wire [1:0] id_aluOp, id_regDst, id_memtoReg;
ControlUnit ctlUnit(id_regDst, id_aluSrc, id_memtoReg, id_regWrite, id_memRead,
            id_memWrite, branch, id_aluOp, IF_ID_opCode, jump);

// Connect relevant fields from IF/ID and ID/EX registers to hazard inputs
// Connect outputs that are sent to the IF stage to the wire defined at top
// Create wire for mux control output
wire ID_EXRegMuxCon;
HazardDetectionUnit hzrdDtctUnit(
    IF_ID_registerRs, IF_ID_registerRt, ID_EX_registerRt,
    ID_EX_memRead, PCWrite, IF_IDWrite, ID_EXRegMuxCon);

// Connect IF/ID register Rs and Rt fields to register file inputs
assign regRdA = IF_ID_registerRs;
assign regRdB = IF_ID_registerRt;

// Extend sign of immediate field from instruction
wire [31:0] signExtendImm;
assign signExtendImm = {{16{IF_ID_imm[15]}}, IF_ID_imm};

// Calculate target address for both branch and jump and select based on ctrl unit output
wire [31:0] branchTargetAddr, jumpTargetAddr, calcTargetAddr;
assign branchTargetAddr = IF_ID_PC + (signExtendImm << 2);
assign jumpTargetAddr = {IF_ID_PC[31:30], (IF_ID_addr << 2)};
Mux2to1 calcTargetAddrMux(calcTargetAddr, branchTargetAddr, jumpTargetAddr, jump);

// Select between calculated target address and target address from register
// based on opCode and funct
wire jr;
assign jr = IF_ID_opCode === 6'b000000 && IF_ID_funct === 6'b001000;
Mux2to1 targetAddrMux(targetAddr, calcTargetAddr, regDoutA, jr);

// Set PCSrc to use selected target address if jumping or branching and branch condition met or jump reg
// Set IFFlush to same.
assign PCSrc = jump ||(branch && regDoutA === regDoutB) || jr;
assign IFFlush = jump ||(branch && regDoutA === regDoutB) || jr;

// Implement ID stage logic in this block
always @(posedge clk) begin
    // Register file outputs into ID/EX register
    ID_EX_readData1 <= regDoutA;
    ID_EX_readData2 <= regDoutB;

    // Sign extend immediate value and send to ID/EX register
    ID_EX_imm <= signExtendImm;

    // Flush control lines to EX stage if hazard detected
    // Could use muxes, but this seems easier.
    ID_EX_regDst <= ID_EXRegMuxCon ? 0 : id_regDst;
    ID_EX_aluOp <= ID_EXRegMuxCon ? 0 : id_aluOp;
    ID_EX_memtoReg <= ID_EXRegMuxCon ? 0 : id_memtoReg;
    ID_EX_regWrite <= ID_EXRegMuxCon || jr ? 0 : id_regWrite;
    ID_EX_memRead <= ID_EXRegMuxCon ? 0 : id_memRead;
    ID_EX_memWrite <= ID_EXRegMuxCon ? 0 : id_memWrite;
    ID_EX_aluSrc <= ID_EXRegMuxCon ? 0 : id_aluSrc;

    // Pass through values
    ID_EX_registerRs <= IF_ID_registerRs;
    ID_EX_registerRt <= IF_ID_registerRt;
    ID_EX_registerRd <= IF_ID_registerRd;
    ID_EX_funct <= IF_ID_funct;
    ID_EX_shamt <= IF_ID_shamt;
    ID_EX_PC <= IF_ID_PC;
end

//////////////
// EX STAGE //
//////////////

// Instantiate forwarding unit and create wires for its output
wire [1:0] forwardA, forwardB;
forwardingUnit fwdUnit(ID_EX_registerRs, ID_EX_registerRt,
                       EX_MEM_regWrite, EX_MEM_registerRd,
                       MEM_WB_regWrite, MEM_WB_registerRd,
                       forwardA, forwardB);

// Instantiate muxes to select alu inputs and create wires for their outputs
wire [31:0] aluInputA, aluInputB, aluInputBreg;
Mux3to1 aluInptAMux(aluInputA, ID_EX_readData1, WBData, forwardA, EX_MEM_aluResult);
Mux3to1 aluInptBMux(aluInputBreg, ID_EX_readData2, WBData, forwardB, EX_MEM_aluResult);
Mux2to1 regOrImmMux(aluInputB, aluInputBreg, ID_EX_imm, ID_EX_aluSrc);

// Instantiate alu control unit and create wires for its output
wire [3:0] operation;
ALUControlUnit aluCtl(operation, ID_EX_aluOp, ID_EX_funct);

// Instantiate alu and create wires for its output
wire [31:0] aluResult;
wire zero;
alu alu(aluInputA, aluInputB, operation, zero, aluResult);

// Instantiate mux to control destination register and create wire for its output
wire [31:0] destinationReg;
Mux3to1 destRegMux(destinationReg, {27'b0,ID_EX_registerRt}, {27'b0,ID_EX_registerRd}, ID_EX_regDst, 31);

// Implement EX stage logic in this block
always @(posedge clk) begin
    // Write results to EX/MEM register
    EX_MEM_aluResult <= aluResult;
    EX_MEM_zero      <= zero;
    EX_MEM_readData2 <= aluInputBreg;
    EX_MEM_registerRd <= destinationReg[4:0];

    // Pass through values
    EX_MEM_PC         <= ID_EX_PC;
    EX_MEM_memtoReg   <= ID_EX_memtoReg;
    EX_MEM_regWrite   <= ID_EX_regWrite;
    EX_MEM_memRead    <= ID_EX_memRead;
    EX_MEM_memWrite   <= ID_EX_memWrite;
end

///////////////
// MEM STAGE //
///////////////

// Send inputs to memory unit
assign memDataRd = EX_MEM_memRead;
// Always write when load is high
assign memDataWr = EX_MEM_memWrite || load;

// If load, write instToLoad to addrToLoad, otherwise, use values from EX/MEM reg.
Mux2to1 memLoadAddrMux(memDataAddr, EX_MEM_aluResult, addrToLoad, load);
Mux2to1 memLoadDataMux(memDin, EX_MEM_readData2, instToLoad, load);

// Implement MEM stage logic in this block
always @(posedge clk) begin
    // Send data read from memory to interstage register
    MEM_WB_readData <= memDout;

    // Pass through values
    MEM_WB_aluResult  <= EX_MEM_aluResult;
    MEM_WB_memtoReg   <= EX_MEM_memtoReg;
    MEM_WB_regWrite   <= EX_MEM_regWrite;
    MEM_WB_registerRd <= EX_MEM_registerRd;
    MEM_WB_PC         <= EX_MEM_PC;
end

//////////////
// WB STAGE //
//////////////

//Instantiate modules used only by this stage here
Mux3to1 wbMux(WBData, MEM_WB_aluResult, MEM_WB_readData, MEM_WB_memtoReg, MEM_WB_PC);

assign regWrite = MEM_WB_regWrite;
assign regDin = WBData;
assign regWr = MEM_WB_registerRd;

endmodule