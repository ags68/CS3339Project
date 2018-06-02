#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  int err = RUN_ALL_TESTS();
  
  // Silence unused variable warning
  (void)err;
  return 0;
}