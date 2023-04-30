#include <iostream>
#include "lib.h"
#include <cmath>

using namespace std;

class SolveOurSquare : public Solvtask
{
public:
    virtual double f(double x) override
    {
        return 2 * x * x + 5 * x + 3;
    }
};

void read(double &x1, double &x2, double &h)
{
    cout << "-------ENTER THE VALUES-------" << endl;
    cout << "Enter the beginning of interval x1 and the end of interval x2: ";
    cin >> x1 >> x2;
    cout << "Enter the step h: ";
    cin >> h;
    cout << endl;
}
int сheck(double &x1, double &x2, double &h)
{
    if (x2 < x1)
    {
        return 1; // ERROR: x2 is less than x1.
    }
    else if (h > (x2 - x1))
    {
        return 2; // ERROR: x2-x1 is less than h.
    }
}

int main()
{

    double x1, x2, h;

    read(x1, x2, h);
    int count = сheck(x1, x2, h);
    switch (count)
    {
    case 1:
        cout << "ERROR: x2 is less than x1." << endl;
        ;
        break;
    case 2:
        cout << "ERROR: x2 is less than x1." << endl;
        break;
    }

    SolveOurSquare Solvtask;

    Solvtask.func(x1, x2, h);

    return 0;
}