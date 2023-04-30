#include <iostream>
#include <math.h>
#include "matrix.h"
#include "drib.h"

using std::cin;
using std::cout;
using std::endl;

int main()
{
    cout << "Set Int UnsignedIntArray:" << endl;
    UnsignedIntArray<int> a(2, 2);
    cin >> a;
    cout << "UnsignedIntArray a:" << a << endl;

    cout << "Set Double UnsignedIntArray:" << endl;
    UnsignedIntArray<double> b(2, 2);
    cin >> b;
    cout << "UnsignedIntArray b:" << b << endl;

    cout << "Set Faction UnsignedIntArray:" << endl;
    cout << "!!NOTE!! You need type factions like 1 2, that = 1/2, so for each number you need type 2 - upper and down number of faction" << endl;
    UnsignedIntArray<Fraction> c(2, 2);
    cin >> c;
    cout << "UnsignedIntArray c:" << c << endl;

    try
    {
        cout << "x3 Matrices:\n";
        cout << "a:"
             << getx3<int>(a) << endl;
        cout << "b:"
             << getx3<double>(b) << endl;
        cout << "c:"
             << getx3<Fraction>(c) << endl;

        cout << "Min values from Matrices:\n";
        cout << "a: " << getMin<int>(a) << endl;
        cout << "b: " << getMin<double>(b) << endl;
        cout << "c: " << getMin<Fraction>(c) << endl;
    }
    catch (std::invalid_argument &e)
    {
        cout << "Error! " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown error!" << endl;
    }

    return 0;
}
