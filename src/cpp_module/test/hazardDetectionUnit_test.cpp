#include "gtest/gtest.h"
#include "hazardDetectionUnit.h"

TEST(HazardDetectionUnitTest, MemReadNoRegMatch) {
    int IF_ID_RegisterRs = 8,
        IF_ID_RegisterRt = 9,
        ID_EX_RegisterRt = 10,
        ID_EX_MemRead = 1,
        ID_EX_RegMux = 0;

    bool PCWrite = false,
         IF_ID_Write = false;

    // Mem read, no register match
    hazardDetectionUnit(IF_ID_RegisterRs, IF_ID_RegisterRt,
                        ID_EX_RegisterRt, ID_EX_MemRead,
                        PCWrite, IF_ID_Write, ID_EX_RegMux);
    EXPECT_EQ (true, PCWrite);
    EXPECT_EQ (true, IF_ID_Write);
    EXPECT_EQ (0, ID_EX_RegMux)
        << "When IF_ID_RegisterRs is: "<< IF_ID_RegisterRs
        << "\nIF_ID_RegisterRt is: " << IF_ID_RegisterRt
        << "\nID_EX_RegisterRt is: " << ID_EX_RegisterRt
        << "\nID_EX_MemRead is: " << ID_EX_MemRead;
}

TEST(HazardDetectionUnitTest, MemReadRegMatchRs) {
    int IF_ID_RegisterRs = 8,
        IF_ID_RegisterRt = 9,
        ID_EX_RegisterRt = 8,
        ID_EX_MemRead = 1,
        ID_EX_RegMux = 0;

    bool PCWrite = false,
         IF_ID_Write = false;
    // Mem read, register match rs
    ID_EX_RegisterRt = IF_ID_RegisterRs;
    hazardDetectionUnit(IF_ID_RegisterRs, IF_ID_RegisterRt,
                        ID_EX_RegisterRt, ID_EX_MemRead,
                        PCWrite, IF_ID_Write,ID_EX_RegMux);
    EXPECT_EQ (false, PCWrite);
    EXPECT_EQ (false, IF_ID_Write);
    EXPECT_EQ (1, ID_EX_RegMux)
        << "When IF_ID_RegisterRs is: "<< IF_ID_RegisterRs
        << "\nIF_ID_RegisterRt is: " << IF_ID_RegisterRt
        << "\nID_EX_RegisterRt is: " << ID_EX_RegisterRt
        << "\nID_EX_MemRead is: " << ID_EX_MemRead;
}

TEST(HazardDetectionUnitTest, MemReadRegMatchRt) {
    int IF_ID_RegisterRs = 8,
        IF_ID_RegisterRt = 9,
        ID_EX_RegisterRt = 8,
        ID_EX_MemRead = 1,
        ID_EX_RegMux = 0;

    bool PCWrite = false,
         IF_ID_Write = false;

    // Mem read, register match rt
    ID_EX_RegisterRt = IF_ID_RegisterRt;
    hazardDetectionUnit(IF_ID_RegisterRs, IF_ID_RegisterRt,
                        ID_EX_RegisterRt, ID_EX_MemRead,
                        PCWrite, IF_ID_Write,ID_EX_RegMux);
    EXPECT_EQ (false, PCWrite);
    EXPECT_EQ (false, IF_ID_Write);
    EXPECT_EQ (1, ID_EX_RegMux)
        << "When IF_ID_RegisterRs is: "<< IF_ID_RegisterRs
        << "\nIF_ID_RegisterRt is: " << IF_ID_RegisterRt
        << "\nID_EX_RegisterRt is: " << ID_EX_RegisterRt
        << "\nID_EX_MemRead is: " << ID_EX_MemRead;
}

TEST(HazardDetectionUnitTest, NoMemReadRegMatchRt) {
    int IF_ID_RegisterRs = 8,
        IF_ID_RegisterRt = 9,
        ID_EX_RegisterRt = 8,
        ID_EX_MemRead = 1,
        ID_EX_RegMux = 0;

    bool PCWrite = false,
         IF_ID_Write = false;

    // No mem read, register match rt
    ID_EX_MemRead = 0;
    ID_EX_RegisterRt = IF_ID_RegisterRt;
    hazardDetectionUnit(IF_ID_RegisterRs, IF_ID_RegisterRt,
                        ID_EX_RegisterRt, ID_EX_MemRead,
                        PCWrite, IF_ID_Write,ID_EX_RegMux);
    EXPECT_EQ (true, PCWrite);
    EXPECT_EQ (true, IF_ID_Write);
    EXPECT_EQ (0, ID_EX_RegMux)
        << "When IF_ID_RegisterRs is: "<< IF_ID_RegisterRs
        << "\nIF_ID_RegisterRt is: " << IF_ID_RegisterRt
        << "\nID_EX_RegisterRt is: " << ID_EX_RegisterRt
        << "\nID_EX_MemRead is: " << ID_EX_MemRead;
}