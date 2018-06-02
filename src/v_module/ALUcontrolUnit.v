module ALUControlUnit( Operation, ALUOp, Function);
output [3:0] Operation;
reg [3:0] Operation;
input [1:0] ALUOp;
input [5:0] Function;
wire [7:0] ALUControlIn;
assign ALUControlIn = {ALUOp,Function};
always @(ALUControlIn)
casex (ALUControlIn) //based on Figure 4.12 and 4.13 on pg.260-261 in textbook
 8'b00xxxxxx: Operation=4'b0010; //load/store word (add)
 8'bx1xxxxxx: Operation=4'b0110; //branch equal (subtract)
 8'b1xxx0000: Operation=4'b0010; //R-type add
 8'b1xxx0010: Operation=4'b0110; //R-type subtract
 8'b1xxx0101: Operation=4'b0001; //R-type or
 8'b1xxx1010: Operation=4'b0111; //R-type set on less than (slt)
 8'b1x100110: Operation=4'b1101; //R-type xor
 endcase
endmodule