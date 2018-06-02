#include "gtest/gtest.h"
#include "ProcessorTestClass.h"

TEST(MEMStageTest, NoReadNoWrite) {
    ProcessorTestClass procTest;

    int initialMemVal = 2348;
    int EX_MEM_regWrite = 0;
    int EX_MEM_memRead = 0;
    int EX_MEM_memtoReg = 0;
    int EX_MEM_memWrite = 0;
    int EX_MEM_zero = 0;
    int EX_MEM_aluResult = 273;
    int EX_MEM_readData2 = 4569;
    int EX_MEM_registerRd = 7;
    int finalMemVal = -1;
    int MEM_WB_regWrite = -1;
    int MEM_WB_memtoReg = -1;
    int MEM_WB_readData = -1;
    int MEM_WB_aluResult = -1;
    int MEM_WB_registerRd = -1;

    procTest.MEMstageTest(
        initialMemVal,
        EX_MEM_regWrite,
        EX_MEM_memRead,
        EX_MEM_memtoReg,
        EX_MEM_memWrite,
        EX_MEM_zero,
        EX_MEM_aluResult,
        EX_MEM_readData2,
        EX_MEM_registerRd,
        finalMemVal,
        MEM_WB_regWrite,
        MEM_WB_memtoReg,
        MEM_WB_readData,
        MEM_WB_aluResult,
        MEM_WB_registerRd
    );

    EXPECT_EQ (initialMemVal, finalMemVal) << "When EX_MEM_memWrite is : " << EX_MEM_memWrite;
    EXPECT_EQ (EX_MEM_regWrite, MEM_WB_regWrite);
    EXPECT_EQ (EX_MEM_memtoReg, MEM_WB_memtoReg);
    EXPECT_EQ (EX_MEM_aluResult, MEM_WB_aluResult);
    EXPECT_EQ (EX_MEM_registerRd, MEM_WB_registerRd);
}

TEST(MEMStageTest, NoReadWrite) {
    ProcessorTestClass procTest;

    int initialMemVal = 2348;
    int EX_MEM_regWrite = 1;
    int EX_MEM_memRead = 0;
    int EX_MEM_memtoReg = 1;
    int EX_MEM_memWrite = 1;
    int EX_MEM_zero = 1;
    int EX_MEM_aluResult = 273;
    int EX_MEM_readData2 = 4569;
    int EX_MEM_registerRd = 8;
    int finalMemVal = -1;
    int MEM_WB_regWrite = -1;
    int MEM_WB_memtoReg = -1;
    int MEM_WB_readData = -1;
    int MEM_WB_aluResult = -1;
    int MEM_WB_registerRd = -1;

    procTest.MEMstageTest(
        initialMemVal,
        EX_MEM_regWrite,
        EX_MEM_memRead,
        EX_MEM_memtoReg,
        EX_MEM_memWrite,
        EX_MEM_zero,
        EX_MEM_aluResult,
        EX_MEM_readData2,
        EX_MEM_registerRd,
        finalMemVal,
        MEM_WB_regWrite,
        MEM_WB_memtoReg,
        MEM_WB_readData,
        MEM_WB_aluResult,
        MEM_WB_registerRd
    );

    EXPECT_EQ (EX_MEM_readData2, finalMemVal) << "When EX_MEM_memWrite is : " << EX_MEM_memWrite;
    EXPECT_EQ (EX_MEM_regWrite, MEM_WB_regWrite);
    EXPECT_EQ (EX_MEM_memtoReg, MEM_WB_memtoReg);
    EXPECT_EQ (EX_MEM_aluResult, MEM_WB_aluResult);
    EXPECT_EQ (EX_MEM_registerRd, MEM_WB_registerRd);
}

TEST(MEMStageTest, ReadNoWrite) {
    ProcessorTestClass procTest;

    int initialMemVal = 2348;
    int EX_MEM_regWrite = 0;
    int EX_MEM_memRead = 1;
    int EX_MEM_memtoReg = 2;
    int EX_MEM_memWrite = 0;
    int EX_MEM_zero = 0;
    int EX_MEM_aluResult = 273;
    int EX_MEM_readData2 = 4569;
    int EX_MEM_registerRd = 9;
    int finalMemVal = -1;
    int MEM_WB_regWrite = -1;
    int MEM_WB_memtoReg = -1;
    int MEM_WB_readData = -1;
    int MEM_WB_aluResult = -1;
    int MEM_WB_registerRd = -1;

    procTest.MEMstageTest(
        initialMemVal,
        EX_MEM_regWrite,
        EX_MEM_memRead,
        EX_MEM_memtoReg,
        EX_MEM_memWrite,
        EX_MEM_zero,
        EX_MEM_aluResult,
        EX_MEM_readData2,
        EX_MEM_registerRd,
        finalMemVal,
        MEM_WB_regWrite,
        MEM_WB_memtoReg,
        MEM_WB_readData,
        MEM_WB_aluResult,
        MEM_WB_registerRd
    );

    EXPECT_EQ (initialMemVal, finalMemVal) << "When EX_MEM_memWrite is : " << EX_MEM_memWrite;
    EXPECT_EQ (initialMemVal, MEM_WB_readData) << "When EX_MEM_memRead is : " << EX_MEM_memRead;
    EXPECT_EQ (EX_MEM_regWrite, MEM_WB_regWrite);
    EXPECT_EQ (EX_MEM_memtoReg, MEM_WB_memtoReg);
    EXPECT_EQ (EX_MEM_aluResult, MEM_WB_aluResult);
    EXPECT_EQ (EX_MEM_registerRd, MEM_WB_registerRd);
}
