module hazardDetectionUnit_test;

reg [4:0] IF_IDRegisterRs,IF_IDRegisterRt,ID_EXRegisterRt;
reg ID_EXMemRead;
wire PCWrite, IF_IDWrite, ID_EXRegMuxCon;

reg PCWrite_exp, IF_IDWrite_exp, ID_EXRegMuxCon_exp;

HazardDetectionUnit dut(IF_IDRegisterRs,IF_IDRegisterRt,ID_EXRegisterRt,ID_EXMemRead,PCWrite,IF_IDWrite,ID_EXRegMuxCon);
hazardDetectionUnit_testDisplay testdisplay(IF_IDRegisterRs,IF_IDRegisterRt,ID_EXRegisterRt, ID_EXMemRead,
    PCWrite, IF_IDWrite, ID_EXRegMuxCon, PCWrite_exp, IF_IDWrite_exp, ID_EXRegMuxCon_exp);

initial begin
    $display("Testing Verilog Hazard Detection Unit...");
    // MemReadNoRegMatch
    IF_IDRegisterRs  <= 8;
    IF_IDRegisterRt  <= 9;
    ID_EXRegisterRt  <= 10;
    ID_EXMemRead     <= 1;

    // Don't stall
    PCWrite_exp         <= 1;
    IF_IDWrite_exp      <= 1;
    ID_EXRegMuxCon_exp  <= 0;

    #20

    // MemReadRegMatchRs
    IF_IDRegisterRs  <= 8;
    IF_IDRegisterRt  <= 9;
    ID_EXRegisterRt  <= 8;
    ID_EXMemRead     <= 1;

    PCWrite_exp         <= 0;
    IF_IDWrite_exp      <= 0;
    ID_EXRegMuxCon_exp  <= 1;

    #20

    // MemReadRegMatchRt
    IF_IDRegisterRs  <= 8;
    IF_IDRegisterRt  <= 9;
    ID_EXRegisterRt  <= 9;
    ID_EXMemRead     <= 1;

    PCWrite_exp         <= 0;
    IF_IDWrite_exp      <= 0;
    ID_EXRegMuxCon_exp  <= 1;

    #20

    // NoMemReadRegMatchRs
    IF_IDRegisterRs  <= 8;
    IF_IDRegisterRt  <= 9;
    ID_EXRegisterRt  <= 8;
    ID_EXMemRead     <= 0;

    PCWrite_exp         <= 1;
    IF_IDWrite_exp      <= 1;
    ID_EXRegMuxCon_exp  <= 0;

end

endmodule

module hazardDetectionUnit_testDisplay(
    IF_IDRegisterRs,IF_IDRegisterRt,ID_EXRegisterRt, ID_EXMemRead,
    PCWrite, IF_IDWrite, ID_EXRegMuxCon,
    PCWrite_exp, IF_IDWrite_exp, ID_EXRegMuxCon_exp
);

input [4:0] IF_IDRegisterRs,IF_IDRegisterRt,ID_EXRegisterRt;
input ID_EXMemRead;
input PCWrite, IF_IDWrite, ID_EXRegMuxCon;

input PCWrite_exp, IF_IDWrite_exp, ID_EXRegMuxCon_exp;

always @(IF_IDRegisterRs or IF_IDRegisterRt or ID_EXRegisterRt or ID_EXMemRead) begin
    #20
    if (PCWrite != PCWrite_exp) begin
        $display("Hazard Detection Unit FAILURE: PCWrite (0b%01b) != expected (0b%01b), when IF_IDRegisterRs = 0b%05b, IF_IDRegisterRt = 0b%05b, ID_EXRegisterRt = 0b%05b, ID_EXMemRead = 0b%01b",
                PCWrite, PCWrite_exp, IF_IDRegisterRs, IF_IDRegisterRt, ID_EXRegisterRt, ID_EXMemRead);
    end

    if (IF_IDWrite != IF_IDWrite_exp) begin
        $display("Hazard Detection Unit FAILURE: IF_IDWrite (0b%01b) != expected (0b%01b), when IF_IDRegisterRs = 0b%05b, IF_IDRegisterRt = 0b%05b, ID_EXRegisterRt = 0b%05b, ID_EXMemRead = 0b%01b",
                 IF_IDWrite, IF_IDWrite_exp, IF_IDRegisterRs, IF_IDRegisterRt, ID_EXRegisterRt, ID_EXMemRead);
    end

    if (ID_EXRegMuxCon != ID_EXRegMuxCon_exp) begin
        $display("Hazard Detection Unit FAILURE: ID_EXRegMuxCon (0b%01b) != expected (0b%01b), when IF_IDRegisterRs = %d, IF_IDRegisterRt = %d, ID_EXRegisterRt = %d, ID_EXMemRead = 0b%01b",
                ID_EXRegMuxCon, ID_EXRegMuxCon_exp, IF_IDRegisterRs, IF_IDRegisterRt, ID_EXRegisterRt, ID_EXMemRead);
    end
end

endmodule