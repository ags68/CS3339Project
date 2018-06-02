module alu(
  din_A, din_B,
  op,
  zero,
  dout
);

input [31:0] din_A, din_B;
input [3:0] op;
output reg zero;
output reg [31:0] dout;

always @(din_A or din_B or op)begin
    case(op)
        4'b0000: dout = din_A & din_B;
        4'b0001: dout = din_A | din_B;
        4'b0010: dout = din_A + din_B;
        4'b0110: dout = din_A - din_B;
        4'b0111: dout = (din_A < din_B);
        4'b1100: dout = ~(din_A | din_B);
        4'b1101: dout = din_A ^ din_B;
        default: dout = 32'h00000000;
    endcase
    if(dout == 0) zero <= 1;
    else zero <= 0;
end

endmodule
