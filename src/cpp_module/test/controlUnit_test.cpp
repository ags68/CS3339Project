#include "gtest/gtest.h"
#include "controlUnit.h"
#include "enums.h"

TEST(CtrlUnitTest, RFORMAT) {
    int opCode = OPCODE_RFORMAT;
    int reg_dst = -1, branch = -1, mem_rd = -1, mem_wr = -1, mem_to_reg = -1, alu_op = -1, alu_src = -1, reg_wr = -1, jump = -1;

    int reg_dst_exp    = 1;
    int alu_op_exp     = 2;
    int alu_src_exp    = 0;
    int branch_exp     = 0;
    int mem_rd_exp     = 0;
    int mem_wr_exp     = 0;
    int reg_wr_exp     = 1;
    int mem_to_reg_exp = 0;
    int jump_exp       = 0;

    controlUnit(opCode, reg_dst, branch, mem_rd, mem_wr, mem_to_reg, alu_op, alu_src, reg_wr, jump);

    EXPECT_EQ(reg_dst_exp, reg_dst) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_op_exp, alu_op) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_src_exp, alu_src) << "When opCode is: " << opCode;
    EXPECT_EQ(branch_exp, branch) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_rd_exp, mem_rd) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_wr_exp, mem_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(reg_wr_exp, reg_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_to_reg_exp, mem_to_reg) << "When opCode is: " << opCode;
    EXPECT_EQ(jump_exp, jump) << "When opCode is: " << opCode;
}

TEST(CtrlUnitTest, J) {
    int opCode = OPCODE_J;
    int reg_dst = -1, branch = -1, mem_rd = -1, mem_wr = -1, mem_to_reg = -1, alu_op = -1, alu_src = -1, reg_wr = -1, jump = -1;

    int mem_rd_exp     = 0;
    int mem_wr_exp     = 0;
    int reg_wr_exp     = 0;
    int jump_exp       = 1;

    controlUnit(opCode, reg_dst, branch, mem_rd, mem_wr, mem_to_reg, alu_op, alu_src, reg_wr, jump);

    EXPECT_EQ(mem_rd_exp, mem_rd) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_wr_exp, mem_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(reg_wr_exp, reg_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(jump_exp, jump) << "When opCode is: " << opCode;
}

TEST(CtrlUnitTest, JAL) {
    int opCode = OPCODE_JAL;
    int reg_dst = -1, branch = -1, mem_rd = -1, mem_wr = -1, mem_to_reg = -1, alu_op = -1, alu_src = -1, reg_wr = -1, jump = -1;

    int reg_dst_exp    = 2;
    int mem_rd_exp     = 0;
    int mem_wr_exp     = 0;
    int reg_wr_exp     = 1;
    int mem_to_reg_exp = 2;
    int jump_exp       = 1;

    controlUnit(opCode, reg_dst, branch, mem_rd, mem_wr, mem_to_reg, alu_op, alu_src, reg_wr, jump);

    EXPECT_EQ(reg_dst_exp, reg_dst) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_rd_exp, mem_rd) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_wr_exp, mem_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(reg_wr_exp, reg_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_to_reg_exp, mem_to_reg) << "When opCode is: " << opCode;
    EXPECT_EQ(jump_exp, jump) << "When opCode is: " << opCode;
}

TEST(CtrlUnitTest, BEQ) {
    int opCode = OPCODE_BEQ;
    int reg_dst = -1, branch = -1, mem_rd = -1, mem_wr = -1, mem_to_reg = -1, alu_op = -1, alu_src = -1, reg_wr = -1, jump = -1;

    int alu_op_exp     = 1;
    int alu_src_exp    = 0;
    int branch_exp     = 1;
    int mem_rd_exp     = 0;
    int mem_wr_exp     = 0;
    int reg_wr_exp     = 0;
    int jump_exp       = 0;

    controlUnit(opCode, reg_dst, branch, mem_rd, mem_wr, mem_to_reg, alu_op, alu_src, reg_wr, jump);

    EXPECT_EQ(alu_op_exp, alu_op) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_src_exp, alu_src) << "When opCode is: " << opCode;
    EXPECT_EQ(branch_exp, branch) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_rd_exp, mem_rd) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_wr_exp, mem_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(reg_wr_exp, reg_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(jump_exp, jump) << "When opCode is: " << opCode;
}

TEST(CtrlUnitTest, ADDI) {
    int opCode = OPCODE_ADDI;
    int reg_dst = -1, branch = -1, mem_rd = -1, mem_wr = -1, mem_to_reg = -1, alu_op = -1, alu_src = -1, reg_wr = -1, jump = -1;

    int reg_dst_exp    = 0;
    int alu_op_exp     = 0;
    int alu_src_exp    = 1;
    int branch_exp     = 0;
    int mem_rd_exp     = 0;
    int mem_wr_exp     = 0;
    int reg_wr_exp     = 1;
    int mem_to_reg_exp = 0;
    int jump_exp       = 0;

    controlUnit(opCode, reg_dst, branch, mem_rd, mem_wr, mem_to_reg, alu_op, alu_src, reg_wr, jump);

    EXPECT_EQ(reg_dst_exp, reg_dst) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_op_exp, alu_op) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_src_exp, alu_src) << "When opCode is: " << opCode;
    EXPECT_EQ(branch_exp, branch) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_rd_exp, mem_rd) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_wr_exp, mem_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(reg_wr_exp, reg_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_to_reg_exp, mem_to_reg) << "When opCode is: " << opCode;
    EXPECT_EQ(jump_exp, jump) << "When opCode is: " << opCode;
}

TEST(CtrlUnitTest, SUBI) {
    int opCode = OPCODE_SUBI;
    int reg_dst = -1, branch = -1, mem_rd = -1, mem_wr = -1, mem_to_reg = -1, alu_op = -1, alu_src = -1, reg_wr = -1, jump = -1;

    int reg_dst_exp    = 0;
    int alu_op_exp     = 1;
    int alu_src_exp    = 1;
    int branch_exp     = 0;
    int mem_rd_exp     = 0;
    int mem_wr_exp     = 0;
    int reg_wr_exp     = 1;
    int mem_to_reg_exp = 0;
    int jump_exp       = 0;

    controlUnit(opCode, reg_dst, branch, mem_rd, mem_wr, mem_to_reg, alu_op, alu_src, reg_wr, jump);

    EXPECT_EQ(reg_dst_exp, reg_dst) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_op_exp, alu_op) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_src_exp, alu_src) << "When opCode is: " << opCode;
    EXPECT_EQ(branch_exp, branch) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_rd_exp, mem_rd) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_wr_exp, mem_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(reg_wr_exp, reg_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_to_reg_exp, mem_to_reg) << "When opCode is: " << opCode;
    EXPECT_EQ(jump_exp, jump) << "When opCode is: " << opCode;
}

TEST(CtrlUnitTest, LW) {
    int opCode = OPCODE_LW;
    int reg_dst = -1, branch = -1, mem_rd = -1, mem_wr = -1, mem_to_reg = -1, alu_op = -1, alu_src = -1, reg_wr = -1, jump = -1;

    int reg_dst_exp    = 0;
    int alu_op_exp     = 0;
    int alu_src_exp    = 1;
    int branch_exp     = 0;
    int mem_rd_exp     = 1;
    int mem_wr_exp     = 0;
    int reg_wr_exp     = 1;
    int mem_to_reg_exp = 1;
    int jump_exp       = 0;

    controlUnit(opCode, reg_dst, branch, mem_rd, mem_wr, mem_to_reg, alu_op, alu_src, reg_wr, jump);

    EXPECT_EQ(reg_dst_exp, reg_dst) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_op_exp, alu_op) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_src_exp, alu_src) << "When opCode is: " << opCode;
    EXPECT_EQ(branch_exp, branch) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_rd_exp, mem_rd) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_wr_exp, mem_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(reg_wr_exp, reg_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_to_reg_exp, mem_to_reg) << "When opCode is: " << opCode;
    EXPECT_EQ(jump_exp, jump) << "When opCode is: " << opCode;
}

TEST(CtrlUnitTest, SW) {
    int opCode = OPCODE_SW;
    int reg_dst = -1, branch = -1, mem_rd = -1, mem_wr = -1, mem_to_reg = -1, alu_op = -1, alu_src = -1, reg_wr = -1, jump = -1;

    int alu_op_exp     = 0;
    int alu_src_exp    = 1;
    int branch_exp     = 0;
    int mem_rd_exp     = 0;
    int mem_wr_exp     = 1;
    int reg_wr_exp     = 0;
    int jump_exp       = 0;

    controlUnit(opCode, reg_dst, branch, mem_rd, mem_wr, mem_to_reg, alu_op, alu_src, reg_wr, jump);

    EXPECT_EQ(alu_op_exp, alu_op) << "When opCode is: " << opCode;
    EXPECT_EQ(alu_src_exp, alu_src) << "When opCode is: " << opCode;
    EXPECT_EQ(branch_exp, branch) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_rd_exp, mem_rd) << "When opCode is: " << opCode;
    EXPECT_EQ(mem_wr_exp, mem_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(reg_wr_exp, reg_wr) << "When opCode is: " << opCode;
    EXPECT_EQ(jump_exp, jump) << "When opCode is: " << opCode;
}