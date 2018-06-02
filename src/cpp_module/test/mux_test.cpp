#include "gtest/gtest.h"
#include "mux.h"

TEST(MuxTest, 2x1Mux) {
    int a = 24, b = 76, dout = 0, select = 0;
    mux_2x1(a,b,select,dout);
    EXPECT_EQ (a, dout) << "When select is: " << select;
    a = 0;
    mux_2x1(a,b,select,dout);
    EXPECT_EQ (a, dout) << "When select is: " << select;
    select = 1;
    mux_2x1(a,b,select,dout);
    EXPECT_EQ (b, dout) << "When select is: " << select;
}

TEST (MuxTest, 3x1Mux) {
    int a = 24, b = 76, c = 132, dout = 0, select = 0;

    select = 0;
    mux_3x1(a,b,c,select,dout);
    EXPECT_EQ (a, dout) << "When select is: " << select;

    a = 0;
    mux_3x1(a,b,c,select,dout);
    EXPECT_EQ (a, dout) << "When select is: " << select;

    select = 1;
    a = 24;
    mux_3x1(a,b,c,select,dout);
    EXPECT_EQ (b, dout) << "When select is: " << select;

    b = 0;
    mux_3x1(a,b,c,select,dout);
    EXPECT_EQ (b, dout) << "When select is: " << select;

    select = 2;
    mux_3x1(a,b,c,select,dout);
    EXPECT_EQ (c, dout) << "When select is: " << select;
}