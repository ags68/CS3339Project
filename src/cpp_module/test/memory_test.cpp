#include "gtest/gtest.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "memory.h"

TEST(MemoryTest, RandomFill) {
    memory mem;
    int memSize = 2048, readData = 0, blockSize = 4;
    int randData[memSize / blockSize];

    /* initialize random seed: */
    srand (time(NULL));

    // Generate random data and fill memory
    for (int address = 0; address < memSize; address += blockSize){
        randData[address / blockSize] = rand();
        mem.write(address, randData[address / blockSize]);
    }

    // Read back data and compare against random data
    for (int address = 0; address < memSize; address += blockSize){
        mem.read(address, readData);
        EXPECT_EQ (randData[address / blockSize], readData) << "When address is : " << address;
    }
}

TEST(MemoryTest, RandomRefill) {
    memory mem;
    int memSize = 512, readData = 0, blockSize = 4;
    int randData[memSize / blockSize];

    /* initialize random seed: */
    srand (time(NULL));

    // Generate random data and fill memory
    for (int address = 0; address < memSize; address += blockSize){
        randData[address / blockSize] = rand();
        mem.write(address, randData[address / blockSize]);
    }

    // Read back data and compare against random data
    for (int address = 0; address < memSize; address += blockSize){
        mem.read(address, readData);
        EXPECT_EQ (randData[address / blockSize], readData) << "When address is : " << address;
    }

    // Regenerate random data and refill memory
    for (int address = 0; address < memSize; address += blockSize){
        randData[address / blockSize] = rand();
        mem.write(address, randData[address / blockSize]);
    }

    // Read back data and compare against random data
    for (int address = 0; address < memSize; address += blockSize){
        mem.read(address, readData);
        EXPECT_EQ (randData[address / blockSize], readData) << "When address is : " << address;
    }
}