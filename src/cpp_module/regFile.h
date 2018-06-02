#ifndef REG_FILE_H
#define REG_FILE_H

class regFile{
    int registers[32] ={0,0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,0,
						0,0,0,0,0,0,0,0};
public:
    void read(int reg_A, int reg_B, int &dout_A, int &dout_B);
    void write(int reg, int din);
};

#endif
