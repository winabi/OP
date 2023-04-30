#ifndef Drib_h
#define Drib_h

#include <iostream>
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::invalid_argument;
using std::istream;
using std::ostream;
#include <cmath>

int findGCD(int a, int b)
{ // алгоритм Евкліда
    if (b == 0)
    {
        return a;
    }
    return findGCD(b, a % b);
}

class Fraction
{
    // Введення та виведення
    friend istream &operator>>(istream &in, Fraction &fraction)
    {
        if (fraction.denominator == 0)
        {
            throw std::invalid_argument("Denominator cannot be zero!");
        }

        return in >> fraction.numerator >> fraction.denominator;
    };
    friend ostream &operator<<(ostream &out, const Fraction &fraction)
    {
        if (fraction.numerator == 0)
        {
            out << 0;
        }
        else if (fraction.denominator == 1)
        {
            out << fraction.numerator;
        }
        else if (abs(fraction.numerator) > abs(fraction.denominator))
        {
            int integerPart;
            if (fraction.numerator == 0)
            {
                integerPart = 0;
            }
            else
            {
                integerPart = fraction.numerator / fraction.denominator;
            }
            int newNumerator = fraction.numerator - integerPart * fraction.denominator;
            if (integerPart != 0)
            {
                out << integerPart << " ";
            }
            out << newNumerator << "/" << fraction.denominator;
        }
        else
        {
            out << fraction.numerator << "/" << fraction.denominator;
        }
        return out;
    }

    // Перевантажені оператори

    friend bool operator>=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return fraction1.numerator * fraction2.denominator >= fraction2.numerator * fraction1.denominator;
    }

    friend bool operator<=(const Fraction &fraction1, const Fraction &fraction2)
    {
        return (fraction1.numerator * fraction2.denominator <= fraction2.numerator * fraction1.denominator);
    }

    friend bool operator>(const Fraction &fraction1, const Fraction &fraction2)
    {
        return (fraction1.numerator * fraction2.denominator > fraction2.numerator * fraction1.denominator);
    }

    friend bool operator<(const Fraction &fraction1, const Fraction &fraction2)
    {
        return (fraction1.numerator * fraction2.denominator < fraction2.numerator * fraction1.denominator);
    }

    friend bool operator>=(const Fraction &fraction1, const int a)
    {
        Fraction fraction2 = Fraction(a, 1);
        return (fraction1.numerator * fraction2.denominator >= fraction2.numerator * fraction1.denominator);
    }

    friend bool operator<=(const Fraction &fraction1, const int a)
    {
        Fraction fraction2 = Fraction(a, 1);
        return (fraction1.numerator * fraction2.denominator <= fraction2.numerator * fraction1.denominator);
    }

    friend bool operator>(const Fraction &fraction1, const int a)
    {
        Fraction fraction2 = Fraction(a, 1);
        return (fraction1.numerator * fraction2.denominator > fraction2.numerator * fraction1.denominator);
    }

    friend bool operator<(const Fraction &fraction1, const int a)
    {
        Fraction fraction2 = Fraction(a, 1);
        return (fraction1.numerator * fraction2.denominator < fraction2.numerator * fraction1.denominator);
    }

private:
    int numerator;   // чисельник
    int denominator; // знаменник
public:
    // Конструктори
    Fraction() { numerator = denominator = 1; };
    Fraction(int numerator, int denominator);

    // Функція скорочення дробу
    void simplify()
    {
        int gcd = findGCD(numerator, denominator);
        if (gcd != 0)
        {
            numerator /= gcd;
            denominator /= gcd;
        }
    }

    // Геттери:
    double getNumerator() { return numerator; }
    double getDenominator() { return denominator; }

    friend Fraction operator*(Fraction fraction1, int a)
    {
        int mulNumerator = fraction1.numerator * a;
        int mulDenominator = fraction1.denominator * 1;

        Fraction mul(mulNumerator, mulDenominator);
        mul.simplify();
        return mul;
    };
};

// Конструктор з параметрами
Fraction::Fraction(int numerator, int denominator)
{
    this->numerator = numerator;
    this->denominator = denominator;
}

#endif