#include <iostream>
#include "lib.h"
#include <cmath>

using namespace std;

double f1(double x)
{
    return sin(x);
}

template <typename T>
class SolveOurSquare
{
private:
    T a;
    T b;
    T c;

public:
    SolveOurSquare(T a, T b, T c)
    {
        this->a = a;
        this->b = b;
        this->c = c;
    }

    T operator()(T x) const
    {
        return a * x * x + b * x + c;
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

    SolveOurSquare<double> f2(2, 5, 3);

    printf("\nOn range [%f; %f], with step %f, for function y = sin(x) number of roots is: %d\n", x1, x2, h, func(f1, x1, x2, h));
    printf("\nOn range [%f; %f], with step %f, for function y = 2x^2 + 5x + 3 number of roots is: %d\n", x1, x2, h, func(f2, x1, x2, h));

    return 0;
}