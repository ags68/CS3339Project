module ControlUnit(RegDst,
                   ALUSrc,
                   MemtoReg,
                   RegWrite,
                   MemRead,
                   MemWrite,
                   Branch,
                   ALUOp,
                   Opcode, 
                   Jump);

output ALUSrc, RegWrite, MemRead, MemWrite, Branch, Jump;
output [1:0] ALUOp, RegDst, MemtoReg;
input [5:0] Opcode;
reg ALUSrc, RegWrite, MemRead, MemWrite, Branch, Jump;
reg [1:0] ALUOp, RegDst, MemtoReg;
always @(*)
casex (Opcode)  // based on Figure 4.22 on pg.269 of textbook 
 6'b000000 : begin // R-format
     RegDst = 2'b01;
     ALUSrc = 1'b0;
     MemtoReg= 2'b00;
     RegWrite= 1'b1;
     MemRead = 1'b0;
     MemWrite= 1'b0;
     Branch = 1'b0;
     ALUOp = 2'b10; // operation determined by function field [5:0] in ALU Control Unit
     Jump = 1'b0;
    end
 6'b100011 : begin // lw
     RegDst = 2'b00;
     ALUSrc = 1'b1;
     MemtoReg= 2'b01;
     RegWrite= 1'b1;
     MemRead = 1'b1;
     MemWrite= 1'b0;
     Branch = 1'b0;
     ALUOp = 2'b00; // always do addition
     Jump = 1'b0;
    end
 6'b101011 : begin // sw
     RegDst = 2'bxx;
     ALUSrc = 1'b1;
     MemtoReg= 2'bxx;
     RegWrite= 1'b0;
     MemRead = 1'b0;
     MemWrite= 1'b1;
     Branch = 1'b0;
     ALUOp = 2'b00; // always do addition
     Jump = 1'b0;
    end
 6'b000100 : begin // beq
     RegDst = 2'bxx;
     ALUSrc = 1'b0;
     MemtoReg= 2'bxx;
     RegWrite= 1'b0;
     MemRead = 1'b0;
     MemWrite= 1'b0;
     Branch = 1'b1;
     ALUOp = 2'b01; // always do subtraction
     Jump = 1'b0;
    end

 6'b000010 : begin // jump
     RegDst = 2'bxx;
     ALUSrc = 1'bx;
     MemtoReg= 2'bxx;
     RegWrite= 1'b0;
     MemRead = 1'b0;
     MemWrite= 1'b0;
     Branch = 1'bx;
     ALUOp = 2'bxx;
     Jump = 1'b1;
    end

6'b000011 : begin // jal
     RegDst = 2'b10;
     ALUSrc = 1'bx;
     MemtoReg= 2'b10;
     RegWrite= 1'b1;
     MemRead = 1'b0;
     MemWrite= 1'b0;
     Branch = 1'bx;
     ALUOp = 2'bxx;
     Jump = 1'b1;
    end

6'b001000 : begin // addi
     RegDst = 2'b00;
     ALUSrc = 1'b1;
     MemtoReg= 2'b00;
     RegWrite= 1'b1;
     MemRead = 1'b0;
     MemWrite= 1'b0;
     Branch = 1'b0;
     ALUOp = 2'b00; // always do addition
     Jump = 1'b0;
    end

6'b001010 : begin //subi
     RegDst = 2'b00;
     ALUSrc = 1'b1;
     MemtoReg= 2'b00;
     RegWrite= 1'b1;
     MemRead = 1'b0;
     MemWrite= 1'b0;
     Branch = 1'b0;
     ALUOp = 2'b01; // always do subtraction
     Jump = 1'b0;
    end

endcase

endmodule