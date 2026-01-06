#include "cee.h"

constexpr int square(int x)
{
    return x * x;
}

consteval int cube(int x)
{
    return x * x * x;
}

int square_add(int x)
{
    int y = 0;
    for (int i = 0; i < x; ++i)
    {
        y += x;
    }
    return y;
}