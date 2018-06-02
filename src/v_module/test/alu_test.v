module alu_test;
reg [31:0] din_A, din_B;
reg [3:0] op;
wire [31:0] dout;
wire zero;

alu dut(din_A, din_B, op, zero, dout);

initial begin
    $display("Testing Verilog ALU...");
    din_A <= 32'h0000BEEF;
    din_B <= 32'h0000CAFE;
    op <= 4'b0000;
    #20
    if (dout != din_A & din_B) begin
        $display("ALU FAILURE: dout (0x%08x) != din_A AND din_B (0x%08x), when op = 0b%04b", dout, din_A & din_B, op);
    end
    op <= 4'b0001;
    #20
    if (dout != (din_A | din_B)) begin
        $display("ALU FAILURE: dout (0x%08x) != din_A OR din_B (0x%08x), when op = 0b%04b", dout, din_A | din_B, op);
    end
    op <= 4'b0010;
    #20
    if (dout != (din_A + din_B)) begin
        $display("ALU FAILURE: dout (0x%08x) != din_A + din_B (0x%08x), when op = 0b%04b", dout, din_A + din_B, op);
    end
    op <= 4'b0110;
    #20
    if (dout != (din_A - din_B)) begin
        $display("ALU FAILURE: dout (0x%08x) != din_A - din_B (0x%08x), when op = 0b%04b", dout, din_A - din_B, op);
    end
    op <= 4'b1100;
    #20
    if (dout != ~(din_A | din_B)) begin
        $display("ALU FAILURE: dout (0x%08x) != din_A NOR din_B (0x%08x), when op = 0b%04b", dout, ~(din_A | din_B), op);
    end
    op <= 4'b1101;
    #20
    if (dout != (din_A ^ din_B)) begin
        $display("ALU FAILURE: dout (0x%08x) != din_A XOR din_B (0x%08x), when op = 0b%04b", dout, din_A ^ din_B, op);
    end
end

endmodule