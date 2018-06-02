#include "gtest/gtest.h"
#include "ProcessorTestClass.h"
#include "enums.h"

TEST(IDStageTest, NoStallNoJumpOrBranch) {
    ProcessorTestClass procTest;

        int regRsVal = 2354;
        int regRtVal = 6798;
        int IF_ID_PC = 374;
        int IF_ID_opCode = OPCODE_RFORMAT;
        int IF_ID_registerRs = 8;
        int IF_ID_registerRt = 9;
        int IF_ID_registerRd = 10;
        int IF_ID_shamt = 5;
        int IF_ID_funct = FUNCT_ADD;
        int IF_ID_immediate = 240;
        int ID_EX_memRead_initial = 0;
        int ID_EX_registerRt_initial = 7;
        int ID_EX_regDst = -1;
        int ID_EX_aluOp = -1;
        int ID_EX_aluSrc = -1;
        int ID_EX_memtoReg = -1;
        int ID_EX_regWrite = -1;
        int ID_EX_memRead = -1;
        int ID_EX_memWrite = -1;
        int ID_EX_readData1 = -1;
        int ID_EX_readData2 = -1;
        int ID_EX_registerRs = -1;
        int ID_EX_registerRt = -1;
        int ID_EX_registerRd = -1;
        int ID_EX_shamt = -1;
        int ID_EX_funct = -1;
        int ID_EX_immediate = -1;
        int PCSrcVal = -1;
        int PCWriteVal = -1;
        int IF_IDWriteVal = -1;
        int IFFlushVal = -1;
        int targetAddrVal = -1;

    procTest.IDstageTest(
        regRsVal,
        regRtVal,
        IF_ID_PC,
        IF_ID_opCode,
        IF_ID_registerRs,
        IF_ID_registerRt,
        IF_ID_registerRd,
        IF_ID_shamt,
        IF_ID_funct,
        IF_ID_immediate,
        ID_EX_memRead_initial,
        ID_EX_registerRt_initial,
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
        PCSrcVal,
        PCWriteVal,
        IF_IDWriteVal,
        IFFlushVal,
        targetAddrVal
    );

    EXPECT_EQ (1, ID_EX_regDst) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (2, ID_EX_aluOp) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_aluSrc) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_memtoReg) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (1, ID_EX_regWrite) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_memRead) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_memWrite) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, PCSrcVal) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (1, PCWriteVal) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (1, IF_IDWriteVal) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (regRsVal, ID_EX_readData1);
    EXPECT_EQ (regRtVal, ID_EX_readData2);
    EXPECT_EQ (IF_ID_registerRs, ID_EX_registerRs);
    EXPECT_EQ (IF_ID_registerRt, ID_EX_registerRt);
    EXPECT_EQ (IF_ID_registerRd, ID_EX_registerRd);
    EXPECT_EQ (IF_ID_shamt, ID_EX_shamt);
    EXPECT_EQ (IF_ID_funct, ID_EX_funct);
    EXPECT_EQ (IF_ID_immediate, ID_EX_immediate);
}

TEST(IDStageTest, StallNoJumpOrBranch) {
    ProcessorTestClass procTest;

        int regRsVal = 2354;
        int regRtVal = 6798;
        int IF_ID_PC = 374;
        int IF_ID_opCode = OPCODE_RFORMAT;
        int IF_ID_registerRs = 8;
        int IF_ID_registerRt = 9;
        int IF_ID_registerRd = 10;
        int IF_ID_shamt = 5;
        int IF_ID_funct = FUNCT_ADD;
        int IF_ID_immediate = 240;
        int ID_EX_memRead_initial = 1;
        int ID_EX_registerRt_initial = 8;
        int ID_EX_regDst = -1;
        int ID_EX_aluOp = -1;
        int ID_EX_aluSrc = -1;
        int ID_EX_memtoReg = -1;
        int ID_EX_regWrite = -1;
        int ID_EX_memRead = -1;
        int ID_EX_memWrite = -1;
        int ID_EX_readData1 = -1;
        int ID_EX_readData2 = -1;
        int ID_EX_registerRs = -1;
        int ID_EX_registerRt = -1;
        int ID_EX_registerRd = -1;
        int ID_EX_shamt = -1;
        int ID_EX_funct = -1;
        int ID_EX_immediate = -1;
        int PCSrcVal = -1;
        int PCWriteVal = -1;
        int IF_IDWriteVal = -1;
        int IFFlushVal = -1;
        int targetAddrVal = -1;

    procTest.IDstageTest(
        regRsVal,
        regRtVal,
        IF_ID_PC,
        IF_ID_opCode,
        IF_ID_registerRs,
        IF_ID_registerRt,
        IF_ID_registerRd,
        IF_ID_shamt,
        IF_ID_funct,
        IF_ID_immediate,
        ID_EX_memRead_initial,
        ID_EX_registerRt_initial,
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
        PCSrcVal,
        PCWriteVal,
        IF_IDWriteVal,
        IFFlushVal,
        targetAddrVal
    );

    EXPECT_EQ (0, ID_EX_regDst) << "When IF_ID_opCode is : " << IF_ID_opCode << "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs<< "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_aluOp) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_aluSrc) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_memtoReg) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_regWrite) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_memRead) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, ID_EX_memWrite) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, PCWriteVal) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (0, IF_IDWriteVal) << "When IF_ID_opCode is : " << IF_ID_opCode<< "\nID_EX_memRead_initial is : " << ID_EX_memRead_initial
        << "\nID_EX_registerRt_initial is : " << ID_EX_registerRt_initial << "\nIF_ID_registerRs is : " << IF_ID_registerRs << "\nIF_ID_registerRs is : " << IF_ID_registerRs;
    EXPECT_EQ (regRsVal, ID_EX_readData1);
    EXPECT_EQ (regRtVal, ID_EX_readData2);
    EXPECT_EQ (IF_ID_registerRs, ID_EX_registerRs);
    EXPECT_EQ (IF_ID_registerRt, ID_EX_registerRt);
    EXPECT_EQ (IF_ID_registerRd, ID_EX_registerRd);
    EXPECT_EQ (IF_ID_shamt, ID_EX_shamt);
    EXPECT_EQ (IF_ID_funct, ID_EX_funct);
    EXPECT_EQ (IF_ID_immediate, ID_EX_immediate);
}