#include "gtest/gtest.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "regFile.h"

TEST(RegFileTest, RandomFill) {
    regFile registerFile;
    int numRegs= 32, dout_A = 0, dout_B = 0;
    int randData[numRegs];

    /* initialize random seed: */
    srand (time(NULL));

    // Generate random data and fill memory
    for (int reg = 0; reg < numRegs; reg++){
        randData[reg] = rand();
        registerFile.write(reg, randData[reg]);
    }

    // Read back data and compare against random data
    for (int reg_A = 0; reg_A < numRegs; reg_A++){
        for (int reg_B = 0; reg_B < numRegs; reg_B++){
            registerFile.read(reg_A, reg_B, dout_A, dout_B);
            ASSERT_EQ (randData[reg_A], dout_A) << "When reg_A is: " << reg_A;
            ASSERT_EQ (randData[reg_B], dout_B) << "When reg_B is: " << reg_B;
        }
    }
}

TEST(RegFileTest, RandomRefill) {
    regFile registerFile;
    int numRegs = 32, dout_A = 0, dout_B = 0;
    int randData[numRegs];

    /* initialize random seed: */
    srand (time(NULL));

    // Generate random data and fill memory
    for (int reg = 0; reg < numRegs; reg++){
        randData[reg] = rand();
        registerFile.write(reg, randData[reg]);
    }

    // Regenerate random data and refill memory
    for (int reg = 0; reg < numRegs; reg++){
        randData[reg] = rand();
        registerFile.write(reg, randData[reg]);
    }

    // Read back data and compare against random data
    for (int reg_A = 0; reg_A < numRegs; reg_A++){
        for (int reg_B = 0; reg_B < numRegs; reg_B++){
            registerFile.read(reg_A, reg_B, dout_A, dout_B);
            ASSERT_EQ (randData[reg_A], dout_A) << "When reg_A is: " << reg_A;
            ASSERT_EQ (randData[reg_B], dout_B) << "When reg_B is: " << reg_B;
        }
    }
}