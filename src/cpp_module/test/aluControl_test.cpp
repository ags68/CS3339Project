#include "gtest/gtest.h"
#include "aluControl.h"
#include "enums.h"

TEST(ALUCtrlTest, LW_SW) {
    int alu_op = 0, funct = 37, op = 0;
    aluControl(alu_op, funct, op);
    EXPECT_EQ(ALU_ADD, op);
} 

TEST(ALUCtrlTest, BEQ) {
    int alu_op = 1, funct = 37, op = 0;
    aluControl(alu_op, funct, op);
    EXPECT_EQ(ALU_SUB, op);
}

TEST(ALUCtrlTest, ADD) {
    int alu_op = 2, funct = FUNCT_ADD, op = 0;
    aluControl(alu_op, funct, op);
    EXPECT_EQ(ALU_ADD, op);
}

TEST(ALUCtrlTest, SUB) {
    int alu_op = 2, funct = FUNCT_SUB, op = 0;
    aluControl(alu_op, funct, op);
    EXPECT_EQ(ALU_SUB, op);
}

TEST(ALUCtrlTest, XOR) {
    int alu_op = 2, funct = FUNCT_XOR, op = 0;
    aluControl(alu_op, funct, op);
    EXPECT_EQ(ALU_XOR, op);
}
