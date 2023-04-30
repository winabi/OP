#ifndef DICHOTOMY_H
#define DICHOTOMY_H

#include <cmath>

template <typename F>
int func(F f, double x1, double x2, double h)
{
    int count = 0;
    for (int x = x1; x <= x2; x += h)
    {
        double y;
        y = f(x);
        if (y > -0.0001 && y < 0.0001)
        {
            count++;
        };
    }
    return count;
}

#endif