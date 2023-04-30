#ifndef ROOTS_H
#define ROOTS_H

#include <cmath>

template <typename F>
int find_roots(F f, double x1, double x2, double eps)
{
    int count = 0;
    double a = x1;
    double b = x2;
    while (b - a >= eps)
    {
        double c = (a + b) / 2.0;
        double fc = f(c);
        if (fc == 0.0)
        {
            count++;
            break;
        }
        if (f(a) * fc < 0)
        {
            b = c;
        }
        else
        {
            a = c;
        }
    }
    return count;
}

template <typename F>
F derivative(F f)
{
    return [f](double x)
    {
        const double h = 1e-6;
        return (f(x + h) - f(x - h)) / (2 * h);
    };
}

#endif
