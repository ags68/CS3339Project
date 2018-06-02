#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "regFile.h"
#include "memory.h"
#include <string>

class processor{
protected:
    regFile registerFile;
    memory memoryUnit;

    int PC;

    typedef struct IF_ID_Reg_struct{
        int PC;
        int opCode;
        int registerRs;
        int registerRt;
        int registerRd;
        int shamt;
        int funct;
        int immediate;
        int address;
    } IF_ID_Reg;

    typedef struct ID_EX_Reg_struct{
        int PC;
        int regDst;
        int regWrite;
        int memRead;
        int memtoReg;
        int aluOp;
        int memWrite;
        int aluSrc;
        int readData1;
        int readData2;
        int registerRs;
        int registerRt;
        int registerRd;
        int shamt;
        int funct;
        int immediate;
    } ID_EX_Reg;

    typedef struct EX_MEM_Reg_struct{
        int PC;
        int regWrite;
        int memRead;
        int memtoReg;
        int memWrite;
        int zero;
        int aluResult;
        int readData2;
        int registerRd;
    } EX_MEM_Reg;

    typedef struct MEM_WB_Reg_struct{
        int PC;
        int regWrite;
        int memtoReg;
        int readData;
        int aluResult;
        int registerRd;
    } MEM_WB_Reg;

    // Interstage registers
    // Only write to *_write and read from *_read.
    // At start of cycle, copy from write to read, ie: *_read = *_write;
    IF_ID_Reg  IF_ID_write;
    IF_ID_Reg  IF_ID_read;
    ID_EX_Reg  ID_EX_write;
    ID_EX_Reg  ID_EX_read;
    EX_MEM_Reg EX_MEM_write;
    EX_MEM_Reg EX_MEM_read;
    MEM_WB_Reg MEM_WB_write;
    MEM_WB_Reg MEM_WB_read;

    // Control signals from ID stage to IF stage
    int PCSrc, IFFlush, targetAddr;
    bool PCWrite, IF_IDWrite;

    // Data from WB stage used by forwarding unit in EX stage
    int WBData;

    void IFstage();
    void IDstage();
    void EXstage();
    void MEMstage();
    void WBstage();

public:
    void load(int inst, int instAddr);
    void clock();
    void readReg(int regNumber, int &regValue);
};

#endif
