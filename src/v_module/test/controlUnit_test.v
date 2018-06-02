module controlUnit_test;

reg [5:0] Opcode;
wire ALUSrc, RegWrite, MemRead, MemWrite, Branch, Jump;
wire [1:0] ALUOp, RegDst, MemtoReg;

reg ALUSrc_Exp,RegWrite_Exp,MemRead_Exp,MemWrite_Exp,Branch_Exp,Jump_Exp;
reg [1:0] ALUOp_Exp, RegDst_Exp, MemtoReg_Exp;

wire [5:0] OPCODE_RFORMAT = 'b000000;
wire [5:0] OPCODE_J       = 'b000010;
wire [5:0] OPCODE_JAL     = 'b000011;
wire [5:0] OPCODE_BEQ     = 'b000100;
wire [5:0] OPCODE_ADDI    = 'b001000;
wire [5:0] OPCODE_SUBI    = 'b001010;
wire [5:0] OPCODE_LW      = 'b100011;
wire [5:0] OPCODE_SW      = 'b101011;

ControlUnit dut(RegDst,ALUSrc,MemtoReg,RegWrite,MemRead,MemWrite,Branch,ALUOp,Opcode, Jump);
controlUnit_testDisplay testdisplay(Opcode,RegDst,ALUSrc,MemtoReg,RegWrite,MemRead,MemWrite,Branch,Jump,ALUOp,
    RegDst_Exp,ALUSrc_Exp,MemtoReg_Exp,RegWrite_Exp,MemRead_Exp,MemWrite_Exp,Branch_Exp,Jump_Exp,ALUOp_Exp);

initial begin
    $display("Testing Verilog Control Unit...");
    Opcode <= OPCODE_RFORMAT;
    ALUOp_Exp <= 2;
    RegDst_Exp <= 1;
    ALUSrc_Exp <= 0;
    MemtoReg_Exp <= 0;
    RegWrite_Exp <= 1;
    MemRead_Exp <= 0;
    MemWrite_Exp <= 0;
    Branch_Exp <= 0;
    Jump_Exp <= 0;

    #20
    Opcode <= OPCODE_J;
    ALUOp_Exp <= 0;
    RegDst_Exp <= 0;
    ALUSrc_Exp <= 0;
    MemtoReg_Exp <= 0;
    RegWrite_Exp <= 0;
    MemRead_Exp <= 0;
    MemWrite_Exp <= 0;
    Branch_Exp <= 0;
    Jump_Exp <= 1;

    #20
    Opcode <= OPCODE_JAL;
    ALUOp_Exp <= 0;
    RegDst_Exp <= 2;
    ALUSrc_Exp <= 0;
    MemtoReg_Exp <= 2;
    RegWrite_Exp <= 1;
    MemRead_Exp <= 0;
    MemWrite_Exp <= 0;
    Branch_Exp <= 0;
    Jump_Exp <= 1;

    #20
    Opcode <= OPCODE_BEQ;
    ALUOp_Exp <= 1;
    RegDst_Exp <= 0;
    ALUSrc_Exp <= 0;
    MemtoReg_Exp <= 0;
    RegWrite_Exp <= 0;
    MemRead_Exp <= 0;
    MemWrite_Exp <= 0;
    Branch_Exp <= 1;
    Jump_Exp <= 0;

    #20
    Opcode <= OPCODE_LW;
    ALUOp_Exp <= 0;
    RegDst_Exp <= 0;
    ALUSrc_Exp <= 1;
    MemtoReg_Exp <= 1;
    RegWrite_Exp <= 1;
    MemRead_Exp <= 1;
    MemWrite_Exp <= 0;
    Branch_Exp <= 0;
    Jump_Exp <= 0;

    #20
    Opcode <= OPCODE_SW;
    ALUOp_Exp <= 0;
    RegDst_Exp <= 0;
    ALUSrc_Exp <= 1;
    MemtoReg_Exp <= 0;
    RegWrite_Exp <= 0;
    MemRead_Exp <= 0;
    MemWrite_Exp <= 1;
    Branch_Exp <= 0;
    Jump_Exp <= 0;

    #20
    Opcode <= OPCODE_ADDI;
    ALUOp_Exp <= 0;
    RegDst_Exp <= 0;
    ALUSrc_Exp <= 1;
    MemtoReg_Exp <= 0;
    RegWrite_Exp <= 1;
    MemRead_Exp <= 0;
    MemWrite_Exp <= 0;
    Branch_Exp <= 0;
    Jump_Exp <= 0;

    #20
    Opcode <= OPCODE_SUBI;
    ALUOp_Exp <= 1;
    RegDst_Exp <= 0;
    ALUSrc_Exp <= 1;
    MemtoReg_Exp <= 0;
    RegWrite_Exp <= 1;
    MemRead_Exp <= 0;
    MemWrite_Exp <= 0;
    Branch_Exp <= 0;
    Jump_Exp <= 0;
end

endmodule

module controlUnit_testDisplay(
    Opcode,
    RegDst,ALUSrc,MemtoReg,RegWrite,MemRead,MemWrite,Branch,Jump,ALUOp,
    RegDst_Exp,ALUSrc_Exp,MemtoReg_Exp,RegWrite_Exp,MemRead_Exp,MemWrite_Exp,Branch_Exp,Jump_Exp,ALUOp_Exp
);

input [5:0] Opcode;
input ALUSrc,RegWrite,MemRead,MemWrite,Branch,Jump;
input [1:0] ALUOp, RegDst, MemtoReg;

input ALUSrc_Exp,RegWrite_Exp,MemRead_Exp,MemWrite_Exp,Branch_Exp,Jump_Exp;
input [1:0] ALUOp_Exp, RegDst_Exp, MemtoReg_Exp;

always @(Opcode) begin
    #20
    if (ALUOp != ALUOp_Exp) begin
        $display("Ctrl Unit FAILURE: ALUOp (0b%02b) != expected (0b%02b), when Opcode = 0b%06b", ALUOp, ALUOp_Exp, Opcode);
    end

    if (RegDst != RegDst_Exp) begin
        $display("Ctrl Unit FAILURE: RegDst (0b%02b) != expected 0b%02b, when Opcode = 0b%06b", RegDst, RegDst_Exp, Opcode);
    end

    if (ALUSrc != ALUSrc_Exp) begin
        $display("Ctrl Unit FAILURE: ALUSrc (0b%01b) != expected 0b%01b, when Opcode = 0b%06b", ALUSrc, ALUSrc_Exp, Opcode);
    end

    if (MemtoReg != MemtoReg_Exp) begin
        $display("Ctrl Unit FAILURE: MemtoReg (0b%02b) != expected 0b%02b, when Opcode = 0b%06b", MemtoReg, MemtoReg_Exp, Opcode);
    end

    if (RegWrite != RegWrite_Exp) begin
        $display("Ctrl Unit FAILURE: RegWrite (0b%01b) != expected 0b%01b, when Opcode = 0b%06b", RegWrite, RegWrite_Exp, Opcode);
    end

    if (MemRead != MemRead_Exp) begin
        $display("Ctrl Unit FAILURE: MemRead (0b%01b) != expected 0b%01b, when Opcode = 0b%06b", MemRead, MemRead_Exp, Opcode);
    end

    if (MemWrite != MemWrite_Exp) begin
        $display("Ctrl Unit FAILURE: MemWrite (0b%01b) != expected 0b%01b, when Opcode = 0b%06b", MemWrite, MemWrite_Exp, Opcode);
    end

    if (Branch != Branch_Exp) begin
        $display("Ctrl Unit FAILURE: Branch (0b%01b) != expected 0b%01b, when Opcode = 0b%06b", Branch, Branch_Exp, Opcode);
    end

    if (Jump != Jump_Exp) begin
        $display("Ctrl Unit FAILURE: Jump (0b%01b) != expected 0b%01b, when Opcode = 0b%06b", Jump, Jump_Exp, Opcode);
    end
end

endmodule