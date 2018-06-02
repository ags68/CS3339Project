#ifndef MEMORY_H
#define MEMORY_H

class memory
{
    int memArray[1024] = {0};
    // Need some sort of data members for storage.
    public:
        void read(int address, int &dout);
        void write(int address, int din);
};

#endif
