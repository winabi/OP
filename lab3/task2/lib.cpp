#include "lib.h"
#include <iostream>
#include <cmath>

using namespace std;

void Solvtask::func(double x1, double x2, double h)
{
    int count = 0;
    for (int x = x1; x <= x2; x += h)
    {
        double y;
        y = sin(x);
        if (y > -0.0001 && y < 0.0001)
        {
            count++;
        };
    }
    cout << "Number of roots is " << count << endl;
}