#ifndef ENUMS_H
#define ENUMS_H

enum opCode {
    OPCODE_RFORMAT = 0b000000,
    OPCODE_J       = 0b000010,
    OPCODE_JAL     = 0b000011,
    OPCODE_BEQ     = 0b000100,
    OPCODE_ADDI    = 0b001000,
    OPCODE_SUBI    = 0b001010,
    OPCODE_LW      = 0b100011,
    OPCODE_SW      = 0b101011};

enum aluop {
    ALUOP_LW_SW = 0b00,
    ALUOP_BEQ   = 0b01,
    ALUOP_Rtype = 0b10};

enum funct {
    FUNCT_ADD = 32,
    FUNCT_SUB = 34,
    FUNCT_AND = 36,
    FUNCT_OR  = 37,
    FUNCT_XOR = 38,
    FUNCT_NOR = 39,
    FUNCT_SLT = 42};

enum op {
    ALU_AND = 0b0000,
    ALU_OR  = 0b0001,
    ALU_ADD = 0b0010,
    ALU_SUB = 0b0110,
    ALU_SLT = 0b0111,
    ALU_NOR = 0b1100,
    ALU_XOR = 0b1101};

#endif