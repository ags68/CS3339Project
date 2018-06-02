#include "forwardingUnit.h"

void forwardingUnit(
    int ID_EX_RegisterRs,
    int ID_EX_RegisterRt,
    int EX_MEM_RegWrite,
    int EX_MEM_RegisterRd,
    int MEM_WB_RegisterRd,
    int MEM_WB_RegWrite,
    int &forwardA,
    int &forwardB)
{
    if (EX_MEM_RegWrite && ((EX_MEM_RegisterRd != 0) && (EX_MEM_RegisterRd == ID_EX_RegisterRs)))
        forwardA = 2;
    else if (MEM_WB_RegWrite && ((MEM_WB_RegisterRd != 0) &&
        !(EX_MEM_RegWrite && (EX_MEM_RegisterRd == 0) &&
        EX_MEM_RegisterRd != ID_EX_RegisterRs) &&
        MEM_WB_RegisterRd == ID_EX_RegisterRs))

        forwardA = 1;
    else
        forwardA = 0;

    if (EX_MEM_RegWrite && ((EX_MEM_RegisterRd != 0) && (EX_MEM_RegisterRd == ID_EX_RegisterRt)))
        forwardB = 2;
    else if (MEM_WB_RegWrite && ((MEM_WB_RegisterRd != 0) &&
        !(EX_MEM_RegWrite && (EX_MEM_RegisterRd == 0) &&
        EX_MEM_RegisterRd != ID_EX_RegisterRt) &&
        MEM_WB_RegisterRd == ID_EX_RegisterRt))

        forwardB = 1;

    else
        forwardB = 0;
}
