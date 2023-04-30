#ifndef Lib_h
#define Lib_h

class Solvtask
{
public:
    void func(double x1, double x2, double h);
    virtual double f(double x) = 0;
};

#endif