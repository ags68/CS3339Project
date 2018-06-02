#include "gtest/gtest.h"
#include "ProcessorTestClass.h"
#include "enums.h"

TEST(EXStageTest, NoReadNoWrite) {
    ProcessorTestClass procTest;

    int ID_EX_regDst = 0;
    int ID_EX_aluOp = 0;
    int ID_EX_aluSrc = 0;
    int ID_EX_memtoReg = 0;
    int ID_EX_regWrite = 0;
    int ID_EX_memRead = 0;
    int ID_EX_memWrite = 0;
    int ID_EX_readData1 = 12;
    int ID_EX_readData2 = 7;
    int ID_EX_registerRs = 7;
    int ID_EX_registerRt = 8;
    int ID_EX_registerRd = 9;
    int ID_EX_shamt = 2;
    int ID_EX_funct = FUNCT_SUB;
    int ID_EX_immediate = 6;
    int EX_MEM_regWrite_initial = 0;
    int EX_MEM_aluResult_initial = 37;
    int EX_MEM_registerRd_initial = 8;
    int MEM_WB_regWrite = 0;
    int MEM_WB_registerRd = 9;
    int EX_MEM_regWrite = -1;
    int EX_MEM_memRead = -1;
    int EX_MEM_memtoReg = -1;
    int EX_MEM_memWrite = -1;
    int EX_MEM_zero = -1;
    int EX_MEM_aluResult = -1;
    int EX_MEM_readData2 = -1;
    int EX_MEM_registerRd = -1;

    procTest.EXstageTest(
        ID_EX_regDst,
        ID_EX_aluOp,
        ID_EX_aluSrc,
        ID_EX_memtoReg,
        ID_EX_regWrite,
        ID_EX_memRead,
        ID_EX_memWrite,
        ID_EX_readData1,
        ID_EX_readData2,
        ID_EX_registerRs,
        ID_EX_registerRt,
        ID_EX_registerRd,
        ID_EX_shamt,
        ID_EX_funct,
        ID_EX_immediate,
        EX_MEM_regWrite_initial,
        EX_MEM_aluResult_initial,
        EX_MEM_registerRd_initial,
        MEM_WB_regWrite,
        MEM_WB_registerRd,
        EX_MEM_regWrite,
        EX_MEM_memRead,
        EX_MEM_memtoReg,
        EX_MEM_memWrite,
        EX_MEM_zero,
        EX_MEM_aluResult,
        EX_MEM_readData2,
        EX_MEM_registerRd
    );

    EXPECT_EQ (ID_EX_regDst ? ID_EX_registerRd : ID_EX_registerRt, EX_MEM_registerRd) << "When EX_MEM_memWrite is : " << EX_MEM_memWrite;
    EXPECT_EQ (ID_EX_regWrite, EX_MEM_regWrite);
    EXPECT_EQ (ID_EX_memRead, EX_MEM_memRead);
    EXPECT_EQ (ID_EX_memtoReg, EX_MEM_memtoReg);
    EXPECT_EQ (ID_EX_memWrite, EX_MEM_memWrite);
}