#ifndef FORWARDING_UNIT_H
#define FORWARDING_UNIT_H

void forwardingUnit(
    int ID_EX_RegisterRs,
    int ID_EX_RegisterRt,
    int EX_MEM_RegWrite,
    int EX_MEM_RegisterRd,
    int MEM_WB_RegisterRd,
    int MEM_WB_RegWrite,
    int &forwardA,
    int &forwardB);

#endif
