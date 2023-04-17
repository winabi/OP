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
    friend Fraction operator+(Fraction fraction1, Fraction fraction2)
    {
        double sumNumerator = fraction1.numerator * fraction2.denominator + fraction1.denominator * fraction2.numerator;
        double sumDenominator = fraction1.denominator * fraction2.denominator;
        Fraction sum(sumNumerator, sumDenominator);
        sum.simplify();
        return sum;
    };

    friend Fraction operator-(Fraction fraction1, Fraction fraction2)
    {
        double subNumerator = fraction1.numerator * fraction2.denominator - fraction1.denominator * fraction2.numerator;
        double subDenominator = fraction1.denominator * fraction2.denominator;

        Fraction sub(subNumerator, subDenominator);
        sub.simplify();
        return sub;
    };

    friend Fraction operator*(Fraction fraction1, Fraction fraction2)
    {
        int mulNumerator = fraction1.numerator * fraction2.numerator;
        int mulDenominator = fraction1.denominator * fraction2.denominator;

        Fraction mul(mulNumerator, mulDenominator);
        mul.simplify();
        return mul;
    };

    friend Fraction operator/(Fraction fraction1, Fraction fraction2)
    {
        int divNumerator = fraction1.numerator * fraction2.denominator;
        int divDenominator = fraction1.denominator * fraction2.numerator;
        Fraction div(divNumerator, divDenominator);
        div.simplify();
        return div;
    };

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
};

// Конструктор з параметрами
Fraction::Fraction(int numerator, int denominator)
{
    this->numerator = numerator;
    this->denominator = denominator;
}

int main()
{
    // Створюємо два об'єкти й читаємо з клавіатури їх координати:
    Fraction fraction1, fraction2;

    cout << "Enter the numerator and denominator with a space in the first fraction: ";
    while (true)
    {
        try
        {
            cin >> fraction1;
            break;
        }
        catch (const invalid_argument &e)
        {
            cerr << e.what() << "\n"; // cerr - поток для виводу помилок
            cerr << "Enter the numerator and denominator with a space in the first fraction: ";
        }
    }
    cout << "Enter the numerator and denominator with a space in the second fraction: ";
    try
    {
        cin >> fraction2;
        if (fraction2.getDenominator() == 0)
        {
            throw invalid_argument("Denominator cannot be zero!");
        }
        cout << "The second fraction is: " << fraction2 << endl;
    }
    catch (const invalid_argument &e)
    {
        cerr << "Invalid input: " << e.what() << endl;
        return 1;
    }

    // Демонструємо роботу перевантажених операцій:
    cout << "Sum of numbers: " << fraction1 + fraction2 << endl;
    cout << "Difference in numbers: " << fraction1 - fraction2 << endl;
    cout << "Multiplication of numbers: " << fraction1 * fraction2 << endl;
    cout << "Division of numbers: " << fraction1 / fraction2 << endl;
    cout << "Greater than: " << (fraction1 > fraction2 ? "true" : "false") << endl;
    cout << "Greater than or equal to: " << (fraction1 >= fraction2 ? "true" : "false") << endl;
    cout << "Less than: " << (fraction1 < fraction2 ? "true" : "false") << endl;
    cout << "Less than or equal to: " << (fraction1 <= fraction2 ? "true" : "false") << endl;

    return 0;
}