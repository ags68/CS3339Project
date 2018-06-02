module Mux2to1 (dout, din_A, din_B, select);
 output [31:0] dout;
 input [31:0] din_A, din_B;
 input select;
 reg [31:0] dout;

 always @(din_A or din_B or select)
 if (select == 1'b0)
 dout = din_A;
 else
 dout = din_B;

 endmodule