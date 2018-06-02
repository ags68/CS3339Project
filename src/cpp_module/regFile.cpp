#include "regFile.h"

void regFile::read(int reg_A, int reg_B, int &dout_A, int &dout_B){
    dout_A = registers[reg_A];
    dout_B = registers[reg_B];
}

void regFile::write(int reg, int din){
    registers[reg] = din;
}
