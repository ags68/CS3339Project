#include "gtest/gtest.h"
#include "alu.h"
#include "enums.h"

TEST(ALUTest, ADD) {
    int a = 24, b = 76, dout = 0;
    bool zero = false;
    alu(a,b,ALU_ADD,zero,dout);
    EXPECT_EQ (a + b, dout) << "When a = " << a << " and b = " << b;
    EXPECT_FALSE(zero) << "When a = " << a << " and b = " << b;
    b = -a;
    alu(a,b,ALU_ADD,zero,dout);
    EXPECT_EQ (a + b, dout) << "When a = " << a << " and b = " << b;
    EXPECT_TRUE(zero) << "When a = " << a << " and b = " << b;
}

TEST(ALUTest, SUB) {
    int a = 24, b = 76, dout = 0;
    bool zero = false;
    alu(a,b,ALU_SUB,zero,dout);
    EXPECT_EQ (a - b, dout) << "When a = " << a << " and b = " << b;
    EXPECT_FALSE(zero) << "When a = " << a << " and b = " << b;
    b = a;
    alu(a,b,ALU_SUB,zero,dout);
    EXPECT_EQ (a - b, dout) << "When a = " << a << " and b = " << b;
    EXPECT_TRUE(zero) << "When a = " << a << " and b = " << b;
}

TEST(ALUTest, XOR) {
    int a = 24, b = 76, dout = 0;
    bool zero = false;
    alu(a,b,ALU_XOR,zero,dout);
    EXPECT_EQ (a ^ b, dout) << "When a = " << a << " and b = " << b;
    EXPECT_FALSE(zero) << "When a = " << a << " and b = " << b;
    b = a;
    alu(a,b,ALU_XOR,zero,dout);
    EXPECT_EQ (a ^ b, dout) << "When a = " << a << " and b = " << b;
    EXPECT_TRUE(zero) << "When a = " << a << " and b = " << b;
}