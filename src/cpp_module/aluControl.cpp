#include "aluControl.h"
#include "enums.h"

void aluControl(int alu_op, int funct, int &op){
    switch (alu_op){
        case ALUOP_LW_SW:
            op = ALU_ADD;
            break;
        case ALUOP_BEQ:
            op = ALU_SUB;
            break;
        case ALUOP_Rtype:
            switch (funct){
                case FUNCT_ADD:
                    op = ALU_ADD;
                    break;
                case FUNCT_SUB:
                    op = ALU_SUB;
                    break;
                case FUNCT_AND:
                    op = ALU_AND;
                    break;
                case FUNCT_OR:
                    op = ALU_OR;
                    break;
                case FUNCT_XOR:
                    op = ALU_XOR;
                    break;
                case FUNCT_NOR:
                    op = ALU_NOR;
                    break;
                case FUNCT_SLT:
                    op = ALU_SLT;
                    break;
                default:
                    op = 0;
            }
            break;
        default:
            op = 0;
    }

}
