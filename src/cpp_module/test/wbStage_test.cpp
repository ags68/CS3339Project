#include "gtest/gtest.h"
#include "ProcessorTestClass.h"

TEST(WBStageTest, NoWriteMemToReg) {
    ProcessorTestClass procTest;

    int initialRegVal = 47;
    int regWrite = 0;
    int memtoReg = 1;
    int readData = 63;
    int aluResult = 120;
    int registerRd = 8;
    int finalRegVal = -1;

    procTest.WBstageTest(initialRegVal, regWrite, memtoReg, readData, aluResult, registerRd, finalRegVal);

    EXPECT_EQ (initialRegVal, finalRegVal) << "When regWrite is : " << regWrite << "\nmemtoReg is : " << memtoReg;
}

TEST(WBStageTest, NoWriteALUToReg) {
    ProcessorTestClass procTest;

    int initialRegVal = 47;
    int regWrite = 0;
    int memtoReg = 0;
    int readData = 63;
    int aluResult = 120;
    int registerRd = 8;
    int finalRegVal = -1;

    procTest.WBstageTest(initialRegVal, regWrite, memtoReg, readData, aluResult, registerRd, finalRegVal);

    EXPECT_EQ (initialRegVal, finalRegVal) << "When regWrite is : " << regWrite << "\nmemtoReg is : " << memtoReg;
}

TEST(WBStageTest, WriteMemToReg) {
    ProcessorTestClass procTest;

    int initialRegVal = 47;
    int regWrite = 1;
    int memtoReg = 1;
    int readData = 63;
    int aluResult = 120;
    int registerRd = 8;
    int finalRegVal = -1;

    procTest.WBstageTest(initialRegVal, regWrite, memtoReg, readData, aluResult, registerRd, finalRegVal);

    EXPECT_EQ (readData, finalRegVal) << "When regWrite is : " << regWrite << "\nmemtoReg is : " << memtoReg;
}

TEST(WBStageTest, WriteALUToReg) {
    ProcessorTestClass procTest;

    int initialRegVal = 47;
    int regWrite = 1;
    int memtoReg = 0;
    int readData = 63;
    int aluResult = 120;
    int registerRd = 8;
    int finalRegVal = -1;

    procTest.WBstageTest(initialRegVal, regWrite, memtoReg, readData, aluResult, registerRd, finalRegVal);

    EXPECT_EQ (aluResult, finalRegVal) << "When regWrite is : " << regWrite << "\nmemtoReg is : " << memtoReg;
}
