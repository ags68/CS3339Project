#include "gtest/gtest.h"
#include "ProcessorTestClass.h"

TEST(IFStageTest, NoBranchNoStall) {
    ProcessorTestClass procTest;

    int PCInitial = 24;
    int expInstr = 12; // Figure out instruction
    int PCSrc = 0;
    int PCWrite = 1;
    int IF_IDWrite = 1;
    int IFFlush = 0;
    int targetAddr = 48;
    int IF_ID_PC_initial = 24;
    int IF_ID_opCode_initial = 0;
    int IF_ID_registerRs_initial = 7;
    int IF_ID_registerRt_initial = 8;
    int IF_ID_registerRd_initial = 9;
    int IF_ID_shamt_initial = 5;
    int IF_ID_funct_initial = 32;
    int IF_ID_immediate_initial = 256;
    int PCFinal = -1;
    int IF_ID_PC_final = -1;
    int IF_ID_opCode_final = -1;
    int IF_ID_registerRs_final = -1;
    int IF_ID_registerRt_final = -1;
    int IF_ID_registerRd_final = -1;
    int IF_ID_shamt_final = -1;
    int IF_ID_funct_final = -1;
    int IF_ID_immediate_final = -1;

    procTest.IFstageTest(
        PCInitial,
        expInstr,
        PCSrc,
        PCWrite,
        IF_IDWrite,
        IFFlush,
        targetAddr,
        IF_ID_PC_initial,
        IF_ID_opCode_initial,
        IF_ID_registerRs_initial,
        IF_ID_registerRt_initial,
        IF_ID_registerRd_initial,
        IF_ID_shamt_initial,
        IF_ID_funct_initial,
        IF_ID_immediate_initial,
        PCFinal,
        IF_ID_PC_final,
        IF_ID_opCode_final,
        IF_ID_registerRs_final,
        IF_ID_registerRt_final,
        IF_ID_registerRd_final,
        IF_ID_shamt_final,
        IF_ID_funct_final,
        IF_ID_immediate_final
    );

    EXPECT_EQ (PCInitial + 4, PCFinal) << "When PCSrc is : " << PCSrc << "PCWrite is : " << PCWrite;
    EXPECT_EQ (PCInitial + 4, IF_ID_PC_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    // Figure out expected instruction parts
}

TEST(IFStageTest, BranchNoStall) {
    ProcessorTestClass procTest;

    int PCInitial = 24;
    int expInstr = 12; // Figure out instruction
    int PCSrc = 1;
    int PCWrite = 1;
    int IF_IDWrite = 1;
    int IFFlush = 1;
    int targetAddr = 48;
    int IF_ID_PC_initial = 24;
    int IF_ID_opCode_initial = -1;
    int IF_ID_registerRs_initial = 7;
    int IF_ID_registerRt_initial = 8;
    int IF_ID_registerRd_initial = 9;
    int IF_ID_shamt_initial = 5;
    int IF_ID_funct_initial = 32;
    int IF_ID_immediate_initial = 256;
    int PCFinal = -1;
    int IF_ID_PC_final = -1;
    int IF_ID_opCode_final = -1;
    int IF_ID_registerRs_final = -1;
    int IF_ID_registerRt_final = -1;
    int IF_ID_registerRd_final = -1;
    int IF_ID_shamt_final = -1;
    int IF_ID_funct_final = -1;
    int IF_ID_immediate_final = -1;

    procTest.IFstageTest(
        PCInitial,
        expInstr,
        PCSrc,
        PCWrite,
        IF_IDWrite,
        IFFlush,
        targetAddr,
        IF_ID_PC_initial,
        IF_ID_opCode_initial,
        IF_ID_registerRs_initial,
        IF_ID_registerRt_initial,
        IF_ID_registerRd_initial,
        IF_ID_shamt_initial,
        IF_ID_funct_initial,
        IF_ID_immediate_initial,
        PCFinal,
        IF_ID_PC_final,
        IF_ID_opCode_final,
        IF_ID_registerRs_final,
        IF_ID_registerRt_final,
        IF_ID_registerRd_final,
        IF_ID_shamt_final,
        IF_ID_funct_final,
        IF_ID_immediate_final
    );

    EXPECT_EQ (targetAddr, PCFinal) << "When PCSrc is : " << PCSrc << "PCWrite is : " << PCWrite;
    EXPECT_EQ (0, IF_ID_PC_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (0, IF_ID_opCode_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (0, IF_ID_registerRs_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (0, IF_ID_registerRt_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (0, IF_ID_registerRd_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (0, IF_ID_shamt_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (0, IF_ID_funct_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (0, IF_ID_immediate_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
}

TEST(IFStageTest, StallNoBranch) {
    ProcessorTestClass procTest;

    int PCInitial = 24;
    int expInstr = 12; 
    int PCSrc = 0;
    int PCWrite = 0;
    int IF_IDWrite = 0;
    int IFFlush = 0;
    int targetAddr = 48;
    int IF_ID_PC_initial = 24;
    int IF_ID_opCode_initial = -1;
    int IF_ID_registerRs_initial = 7;
    int IF_ID_registerRt_initial = 8;
    int IF_ID_registerRd_initial = 9;
    int IF_ID_shamt_initial = 5;
    int IF_ID_funct_initial = 32;
    int IF_ID_immediate_initial = 256;
    int PCFinal = -1;
    int IF_ID_PC_final = -1;
    int IF_ID_opCode_final = -1;
    int IF_ID_registerRs_final = -1;
    int IF_ID_registerRt_final = -1;
    int IF_ID_registerRd_final = -1;
    int IF_ID_shamt_final = -1;
    int IF_ID_funct_final = -1;
    int IF_ID_immediate_final = -1;

    procTest.IFstageTest(
        PCInitial,
        expInstr,
        PCSrc,
        PCWrite,
        IF_IDWrite,
        IFFlush,
        targetAddr,
        IF_ID_PC_initial,
        IF_ID_opCode_initial,
        IF_ID_registerRs_initial,
        IF_ID_registerRt_initial,
        IF_ID_registerRd_initial,
        IF_ID_shamt_initial,
        IF_ID_funct_initial,
        IF_ID_immediate_initial,
        PCFinal,
        IF_ID_PC_final,
        IF_ID_opCode_final,
        IF_ID_registerRs_final,
        IF_ID_registerRt_final,
        IF_ID_registerRd_final,
        IF_ID_shamt_final,
        IF_ID_funct_final,
        IF_ID_immediate_final
    );

    EXPECT_EQ (PCInitial, PCFinal) << "When PCSrc is : " << PCSrc << "PCWrite is : " << PCWrite;
    EXPECT_EQ (IF_ID_PC_initial, IF_ID_PC_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (IF_ID_opCode_initial, IF_ID_opCode_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (IF_ID_registerRs_initial, IF_ID_registerRs_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (IF_ID_registerRt_initial, IF_ID_registerRt_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (IF_ID_registerRd_initial, IF_ID_registerRd_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (IF_ID_shamt_initial, IF_ID_shamt_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (IF_ID_funct_initial, IF_ID_funct_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
    EXPECT_EQ (IF_ID_immediate_initial, IF_ID_immediate_final) << "When IF_IDWrite is : " << IF_IDWrite << "\nIFFlush : " << IFFlush;
}