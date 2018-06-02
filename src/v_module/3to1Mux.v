module Mux3to1 (dout, din_A, din_B, select, din_C);
 output [31:0] dout;
 input [31:0] din_A, din_B, din_C;
 input [1:0] select;
 reg [31:0] dout;

 always @(din_A or din_B or din_C or select)
 if (select == 2'b00)
 dout = din_A;
 else if (select == 2'b01)
 dout = din_B;
 else if (select == 2'b10)
 dout = din_C;

 endmodule