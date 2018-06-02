#ifndef PROCESSOR_TEST_CLASS_H
#define PROCESSOR_TEST_CLASS_H

#include "processor.h"

class ProcessorTestClass : processor{
    public:

    void IFstageTest(
        int PCInitial,
        int expInstr,
        int PCSrcInitial,
        int PCWriteInitial,
        int IF_IDWriteInitial,
        int IFFlushInitial,
        int targetAddrInitial,
        int &IF_ID_PC_initial,
        int &IF_ID_opCode_initial,
        int &IF_ID_registerRs_initial,
        int &IF_ID_registerRt_initial,
        int &IF_ID_registerRd_initial,
        int &IF_ID_shamt_initial,
        int &IF_ID_funct_initial,
        int &IF_ID_immediate_initial,
        int &PCFinal,
        int &IF_ID_PC_final,
        int &IF_ID_opCode_final,
        int &IF_ID_registerRs_final,
        int &IF_ID_registerRt_final,
        int &IF_ID_registerRd_final,
        int &IF_ID_shamt_final,
        int &IF_ID_funct_final,
        int &IF_ID_immediate_final
        );

    void IDstageTest(
        int regRsVal,
        int regRtVal,
        int IF_ID_PC,
        int IF_ID_opCode,
        int IF_ID_registerRs,
        int IF_ID_registerRt,
        int IF_ID_registerRd,
        int IF_ID_shamt,
        int IF_ID_funct,
        int IF_ID_immediate,
        int ID_EX_memRead_initial,
        int ID_EX_registerRd_initial,
        int &ID_EX_regDst,
        int &ID_EX_aluOp,
        int &ID_EX_aluSrc,
        int &ID_EX_memtoReg,
        int &ID_EX_regWrite,
        int &ID_EX_memRead,
        int &ID_EX_memWrite,
        int &ID_EX_readData1,
        int &ID_EX_readData2,
        int &ID_EX_registerRs,
        int &ID_EX_registerRt,
        int &ID_EX_registerRd,
        int &ID_EX_shamt,
        int &ID_EX_funct,
        int &ID_EX_immediate,
        int &PCSrcVal,
        int &PCWriteVal,
        int &IF_IDWriteVal,
        int &IFFlushVal,
        int &targetAddrVal
    );

    void EXstageTest(
        int ID_EX_regDst,
        int ID_EX_aluOp,
        int ID_EX_aluSrc,
        int ID_EX_memtoReg,
        int ID_EX_regWrite,
        int ID_EX_memRead,
        int ID_EX_memWrite,
        int ID_EX_readData1,
        int ID_EX_readData2,
        int ID_EX_registerRs,
        int ID_EX_registerRt,
        int ID_EX_registerRd,
        int ID_EX_shamt,
        int ID_EX_funct,
        int ID_EX_immediate,
        int EX_MEM_regWrite_initial,
        int EX_MEM_aluResult_initial,
        int EX_MEM_registerRd_initial,
        int MEM_WB_regWrite,
        int MEM_WB_registerRd,
        int &EX_MEM_regWrite,
        int &EX_MEM_memRead,
        int &EX_MEM_memtoReg,
        int &EX_MEM_memWrite,
        int &EX_MEM_zero,
        int &EX_MEM_aluResult,
        int &EX_MEM_readData2,
        int &EX_MEM_registerRd
    );

    void MEMstageTest(
        int initialMemVal,
        int EX_MEM_regWrite,
        int EX_MEM_memRead,
        int EX_MEM_memtoReg,
        int EX_MEM_memWrite,
        int EX_MEM_zero,
        int EX_MEM_aluResult,
        int EX_MEM_readData2,
        int EX_MEM_registerRd,
        int &finalMemVal,
        int &MEM_WB_regWrite,
        int &MEM_WB_memtoReg,
        int &MEM_WB_readData,
        int &MEM_WB_aluResult,
        int &MEM_WB_registerRd
    );

    void WBstageTest(
        int initialRegVal,
        int regWrite,
        int memtoReg,
        int readData,
        int aluResult,
        int registerRd,
        int &finalRegVal
    );
};

#endif