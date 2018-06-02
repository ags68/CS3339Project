#include "controlUnit.h"
#include "enums.h"

void controlUnit(
        int opcode,
        int &reg_dst,
        int &branch,
        int &mem_rd,
        int &mem_wr,
        int &mem_to_reg,
        int &alu_op,
        int &alu_src,
        int &reg_wr,
		int &jump
){
	switch(opcode)
	{
		case OPCODE_RFORMAT:			//R-Format
			reg_dst = 1;
			alu_src = 0;
			mem_to_reg = 0;
			reg_wr = 1;
			mem_rd = 0;
			mem_wr = 0;
			branch = 0;
			alu_op = 2;
			jump = 0;
		break;
			
		case OPCODE_LW:				//load word
			reg_dst = 0;
			alu_src = 1;
			mem_to_reg = 1;
			reg_wr = 1;
			mem_rd = 1;
			mem_wr = 0;
			branch = 0;
			alu_op = 0;
			jump = 0;
		break;
		
		case OPCODE_SW:				//store word
			reg_dst = 322;
			alu_src = 1;
			mem_to_reg = 322;
			reg_wr = 0;
			mem_rd = 0;
			mem_wr = 1;
			branch = 0;
			alu_op = 0;
			jump = 0;
		break;
		
		case OPCODE_BEQ:			//branch if equal
			reg_dst = 322;
			alu_src = 0;
			mem_to_reg = 322;
			reg_wr = 0;
			mem_rd = 0;
			mem_wr = 0;
			branch = 1;
			alu_op = 1;
			jump = 0;
		break;		
		
		
		case OPCODE_J:				//jump
			reg_dst = 322;
			alu_src = 322;
			mem_to_reg = 322;
			reg_wr = 0;
			mem_rd = 0;
			mem_wr = 0;
			branch = 322;
			alu_op = 322;
			jump = 1;			
		break;
		
		case OPCODE_JAL:			//jump and link
			reg_dst = 2;
			alu_src = 322;
			mem_to_reg = 2;
			reg_wr = 1;
			mem_rd = 0;
			mem_wr = 0;
			branch = 322;
			alu_op = 322;
			jump = 1;
		break;
		
		case OPCODE_ADDI:			//add immediate
			reg_dst = 0;
			alu_src = 1;
			mem_to_reg = 0;
			reg_wr = 1;
			mem_rd = 0;
			mem_wr = 0;
			branch = 0;
			alu_op = 0;
			jump = 0;				
		break;
		
		case OPCODE_SUBI:			//subtract immediate
			reg_dst = 0;
			alu_src = 1;
			mem_to_reg = 0;
			reg_wr = 1;
			mem_rd = 0;
			mem_wr = 0;
			branch = 0;
			alu_op = 1;
			jump = 0;			
		break;
		
		
	}
}
