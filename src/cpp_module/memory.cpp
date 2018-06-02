#include "memory.h"

void memory::read(int address, int &dout)
{
    address = address / 4;

    dout = memArray[address];
}

void memory::write(int address, int din)
{
    address = address / 4;

    memArray[address] = din;
}
