module forwardingUnit_test;

reg [4:0] ID_EX_RegisterRs, ID_EX_RegisterRt, EX_MEM_RegisterRd, MEM_WB_RegisterRd;
reg EX_MEM_RegWrite, MEM_WB_RegWrite;
wire [1:0] forwardA, forwardB;

reg [1:0] forwardA_exp, forwardB_exp;

forwardingUnit dut(
    ID_EX_RegisterRs, ID_EX_RegisterRt,
    EX_MEM_RegWrite, EX_MEM_RegisterRd,
    MEM_WB_RegWrite, MEM_WB_RegisterRd,
    forwardA, forwardB
);

forwardingUnit_testDisplay testdisplay(
    ID_EX_RegisterRs, ID_EX_RegisterRt,
    EX_MEM_RegWrite, EX_MEM_RegisterRd,
    MEM_WB_RegWrite, MEM_WB_RegisterRd,
    forwardA, forwardB,
    forwardA_exp, forwardB_exp
);

initial begin
    $display("Testing Verilog Forwarding Unit...");
    // Setup
    ID_EX_RegisterRs = 8;
    ID_EX_RegisterRt = 9;
    EX_MEM_RegWrite = 1;
    EX_MEM_RegisterRd = 8;
    MEM_WB_RegWrite = 1;
    MEM_WB_RegisterRd = 9;

    // Expected
    forwardA_exp = 2;
    forwardB_exp = 1;

    #20;

    // Setup
    ID_EX_RegisterRs = 8;
    ID_EX_RegisterRt = 9;
    EX_MEM_RegWrite = 1;
    EX_MEM_RegisterRd = 9;
    MEM_WB_RegWrite = 1;
    MEM_WB_RegisterRd = 8;

    // Expected
    forwardA_exp = 1;
    forwardB_exp = 2;

    #20;

    // Setup
    ID_EX_RegisterRs = 8;
    ID_EX_RegisterRt = 8;
    EX_MEM_RegWrite = 1;
    EX_MEM_RegisterRd = 8;
    MEM_WB_RegWrite = 1;
    MEM_WB_RegisterRd = 8;

    // Expected
    forwardA_exp = 2;
    forwardB_exp = 2;

    #20;

    // Setup
    ID_EX_RegisterRs = 8;
    ID_EX_RegisterRt = 8;
    EX_MEM_RegWrite = 0;
    EX_MEM_RegisterRd = 8;
    MEM_WB_RegWrite = 1;
    MEM_WB_RegisterRd = 8;

    // Expected
    forwardA_exp = 1;
    forwardB_exp = 1;

    #20;

    // Setup
    ID_EX_RegisterRs = 8;
    ID_EX_RegisterRt = 8;
    EX_MEM_RegWrite = 1;
    EX_MEM_RegisterRd = 9;
    MEM_WB_RegWrite = 1;
    MEM_WB_RegisterRd = 8;

    // Expected
    forwardA_exp = 1;
    forwardB_exp = 1;

    #20;

    // Setup
    ID_EX_RegisterRs = 0;
    ID_EX_RegisterRt = 0;
    EX_MEM_RegWrite = 1;
    EX_MEM_RegisterRd = 0;
    MEM_WB_RegWrite = 1;
    MEM_WB_RegisterRd = 0;

    // Expected
    forwardA_exp = 0;
    forwardB_exp = 0;

    #20;

    // Setup
    ID_EX_RegisterRs = 8;
    ID_EX_RegisterRt = 8;
    EX_MEM_RegWrite = 0;
    EX_MEM_RegisterRd = 8;
    MEM_WB_RegWrite = 0;
    MEM_WB_RegisterRd = 8;

    // Expected
    forwardA_exp = 0;
    forwardB_exp = 0;

    #20;

    // Setup
    ID_EX_RegisterRs = 8;
    ID_EX_RegisterRt = 8;
    EX_MEM_RegWrite = 0;
    EX_MEM_RegisterRd = 8;
    MEM_WB_RegWrite = 1;
    MEM_WB_RegisterRd = 9;

    // Expected
    forwardA_exp = 0;
    forwardB_exp = 0;

    #20;

end

endmodule

module forwardingUnit_testDisplay(
    ID_EX_RegisterRs, ID_EX_RegisterRt,
    EX_MEM_RegWrite, EX_MEM_RegisterRd,
    MEM_WB_RegWrite, MEM_WB_RegisterRd,
    forwardA, forwardB,
    forwardA_exp, forwardB_exp
);

input [4:0] ID_EX_RegisterRs, ID_EX_RegisterRt, EX_MEM_RegisterRd, MEM_WB_RegisterRd;
input EX_MEM_RegWrite, MEM_WB_RegWrite;
input [1:0] forwardA, forwardB;

input [1:0] forwardA_exp, forwardB_exp;

always @(*) begin
    #10
    if (forwardA !== forwardA_exp) begin
        $display("Forwarding Unit FAILURE: forwardA (0b%02b) != forwardA_exp (0b%02b), when ID_EX_RegisterRs = $%02d, ID_EX_RegisterRt = $%02d, EX_MEM_RegWrite = 0b%01b, EX_MEM_RegisterRd = $%02d, MEM_WB_RegWrite = 0b%01b, MEM_WB_RegisterRd = $%02d",
                forwardA, forwardA_exp, ID_EX_RegisterRs, ID_EX_RegisterRt, EX_MEM_RegWrite, EX_MEM_RegisterRd, MEM_WB_RegWrite, MEM_WB_RegisterRd);
    end

    if (forwardB !== forwardB_exp) begin
        $display("Forwarding Unit FAILURE: forwardB (0b%02b) != forwardB_exp (0b%02b), when ID_EX_RegisterRs = $%02d, ID_EX_RegisterRt = $%02d, EX_MEM_RegWrite = 0b%01b, EX_MEM_RegisterRd = $%02d, MEM_WB_RegWrite = 0b%01b, MEM_WB_RegisterRd = $%02d",
                forwardB, forwardB_exp, ID_EX_RegisterRs, ID_EX_RegisterRt, EX_MEM_RegWrite, EX_MEM_RegisterRd, MEM_WB_RegWrite, MEM_WB_RegisterRd);
    end

end

endmodule