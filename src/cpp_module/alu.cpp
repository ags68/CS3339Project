#include "alu.h"
#include "enums.h"

void alu(int din_A, int din_B, int op, bool &zero, int &dout){

    switch (op) {
        case ALU_AND:
            dout = din_A & din_B;
            break;
        case ALU_OR:
            dout = din_A | din_B;
            break;
        case ALU_ADD:
            dout = din_A + din_B;
            break;
        case ALU_SUB:
            dout = din_A - din_B;
            break;
        case ALU_SLT:
            dout = din_A < din_B? 1:0;
            break;
        case ALU_NOR:
            dout = ~(din_A | din_B);
            break;
        case ALU_XOR:
            dout = din_A ^ din_B;
            break;
        default:
            dout = 0;
    }

    zero = dout == 0;

}
