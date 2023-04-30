#include <iostream>
#include <cmath>
#include "lib.h"

using namespace std;

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

double f1(double x)
{
    return sin(x);
}

double f2(double x)
{
    return x * x - 4;
}

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
        break;
    case 2:
        cout << "ERROR: x2-x1 is less than h." << endl;
        break;
    }

    SolveOurSquare<double> f3(1, 2, -3);
    cout << "\nOn range [" << x1 << "; " << x2 << "], with step " << h << ", for function y = sin(x), number of roots is: " << find_roots(f1, x1, x2, h) << endl;
    cout << "\nOn range [" << x1 << "; " << x2 << "], with step " << h << ", for function y = x^2 - 4, number of roots is: " << find_roots(f2, x1, x2, h) << endl;
    cout << "\nOn range [" << x1 << "; " << x2 << "], with step " << h << ", for function y = x^2 + 2x - 3, number of roots is: " << find_roots(f3, x1, x2, h) << endl;

    return 0;
}