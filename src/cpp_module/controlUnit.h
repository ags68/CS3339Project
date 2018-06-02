#ifndef CONTROL_UNIT_H
#define CONTROL_UNIT_H

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
        );

#endif
