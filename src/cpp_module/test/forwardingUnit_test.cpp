#include "gtest/gtest.h"
#include "forwardingUnit.h"

TEST(ForwardingUnitTest, ForwardEXMEMtoA) {
    int ID_EX_RegisterRs = 8,
        ID_EX_RegisterRt = 8,
        EX_MEM_RegWrite = 0,
        EX_MEM_RegisterRd = 8,
        MEM_WB_RegisterRd = 8,
        MEM_WB_RegWrite = 0,
        forwardA = 0,
        forwardB = 0;

    int ForwardEXMEMtoA = 2;

    // No write, registers equal and not zero
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardEXMEMtoA, forwardA)
        << "When ID_EX_RegisterRs is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // Write, registers equal and not zero
    EX_MEM_RegWrite = 1;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_EQ (ForwardEXMEMtoA, forwardA)
        << "When ID_EX_RegisterRs is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // No write, registers not equal and not zero
    ++EX_MEM_RegisterRd;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardEXMEMtoA, forwardA)
        << "When ID_EX_RegisterRs is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // No write, registers equal and zero
    EX_MEM_RegisterRd = ID_EX_RegisterRs = 0;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardEXMEMtoA, forwardA)
        << "When ID_EX_RegisterRs is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;
}

TEST(ForwardingUnitTest, ForwardEXMEMtoB) {
    int ID_EX_RegisterRs = 8,
        ID_EX_RegisterRt = 8,
        EX_MEM_RegWrite = 0,
        EX_MEM_RegisterRd = 8,
        MEM_WB_RegisterRd = 8,
        MEM_WB_RegWrite = 0,
        forwardA = 0,
        forwardB = 0;

    int ForwardEXMEMtoB = 2;

    // No write, registers equal and not zero
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardEXMEMtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // Write, registers equal and not zero
    EX_MEM_RegWrite = 1;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_EQ (ForwardEXMEMtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // No write, registers not equal and not zero
    ++EX_MEM_RegisterRd;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardEXMEMtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // No write, registers equal and zero
    EX_MEM_RegisterRd = ID_EX_RegisterRt = 0;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardEXMEMtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;
}

TEST(ForwardingUnitTest, ForwardMEMWBtoA) {
    int ID_EX_RegisterRs = 8,
        ID_EX_RegisterRt = 8,
        EX_MEM_RegWrite = 0,
        EX_MEM_RegisterRd = 8,
        MEM_WB_RegisterRd = 8,
        MEM_WB_RegWrite = 0,
        forwardA = 0,
        forwardB = 0;

    int ForwardMEMWBtoA = 1;

    // No write, registers equal and not zero
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoA, forwardA)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // Write, registers equal and not zero
    MEM_WB_RegWrite = 1;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_EQ (ForwardMEMWBtoA, forwardA)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // Write, registers equal and not zero, EX_MEM forwarding override
    EX_MEM_RegWrite = 1;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoA, forwardA)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // No write, registers not equal and not zero
    ++MEM_WB_RegisterRd;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoA, forwardA)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // No write, registers equal and zero
    MEM_WB_RegisterRd = ID_EX_RegisterRs = 0;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoA, forwardA)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // Write, registers equal and not zero, EX_MEM forwarding override
    EX_MEM_RegisterRd = ID_EX_RegisterRs = 8;
    EX_MEM_RegWrite = 1;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoA, forwardA)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRs
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;
}

TEST(ForwardingUnitTest, ForwardMEMWBtoB) {
    int ID_EX_RegisterRs = 8,
        ID_EX_RegisterRt = 8,
        EX_MEM_RegWrite = 0,
        EX_MEM_RegisterRd = 8,
        MEM_WB_RegisterRd = 8,
        MEM_WB_RegWrite = 0,
        forwardA = 0,
        forwardB = 0;

    int ForwardMEMWBtoB = 1;

    // No write, registers equal and not zero
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // Write, registers equal and not zero
    MEM_WB_RegWrite = 1;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_EQ (ForwardMEMWBtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // Write, registers equal and not zero, EX_MEM forwarding override
    EX_MEM_RegWrite = 1;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // No write, registers not equal and not zero
    ++MEM_WB_RegisterRd;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // No write, registers equal and zero
    MEM_WB_RegisterRd = ID_EX_RegisterRt = 0;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;

    // Write, registers equal and not zero, EX_MEM forwarding override
    EX_MEM_RegisterRd = ID_EX_RegisterRt = 8;
    EX_MEM_RegWrite = 1;
    forwardingUnit(ID_EX_RegisterRs, ID_EX_RegisterRt,
                   EX_MEM_RegWrite, EX_MEM_RegisterRd,
                   MEM_WB_RegisterRd, MEM_WB_RegWrite,
                   forwardA, forwardB);
    EXPECT_NE (ForwardMEMWBtoB, forwardB)
        << "When ID_EX_RegisterRt is: "<< ID_EX_RegisterRt
        << "\nEX_MEM_RegWrite is: " << EX_MEM_RegWrite
        << "\nEX_MEM_RegisterRd is: " << EX_MEM_RegisterRd
        << "\nMEM_WB_RegWrite is: " << MEM_WB_RegWrite
        << "\nMEM_WB_RegisterRd is: " << MEM_WB_RegisterRd;
}