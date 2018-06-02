#include "mux.h"

void mux_2x1(int din_A, int din_B, int select, int &dout)
{
    if (select == 0)
        dout = din_A;
    else
        dout = din_B;
}

void mux_3x1(int din_A, int din_B, int din_C, int select, int &dout)
{
    if (select == 0)
        dout = din_A;
    else if (select == 1)
        dout = din_B;
    else
        dout = din_C;
}
