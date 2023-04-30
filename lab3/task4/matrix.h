#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

template <typename T>
class UnsignedIntArray
{
    // Дружні функції перевантаження операцій виведення та введення:
    friend ostream &operator<<(ostream &out, const UnsignedIntArray &a)
    {
        out << "\nArray:" << endl;
        for (int i = 0; i < a.rows; i++)
        {
            for (int j = 0; j < a.cols; j++)
            {
                out << a.pa[i][j] << "\t";
            }
            out << "\n";
        }
        return out;
    }
    friend istream &operator>>(istream &in, UnsignedIntArray &a)
    {
        cout << "Please enter the elements of the array, row by row:" << endl;
        for (int i = 0; i < a.rows; i++)
        {
            cout << "Row " << i + 1 << ": ";
            for (int j = 0; j < a.cols; j++)
            {
                in >> a.pa[i][j];
                cout << a.pa[i][j] << " ";
            }
            cout << endl;
        }
        return in;
    }

private:
    T **pa;       // вказівник на майбутній масив
    int rows = 0; // поточний розмір масиву
    int cols = 0; // розмір другого розміру масиву (кількість стовпців).
public:
    // Вкладений клас для створення об'єкту-винятку
    class OutOfBounds
    {
        int index; // індекс за межами діапазону
    public:
        OutOfBounds(int i) : index(i) {}       // конструктор
        int getIndex() const { return index; } // геттер для індексу
    };

    // Конструктори:
    UnsignedIntArray() {}
    UnsignedIntArray(int r, int c)
    {
        if (r <= 0)
        {
            throw OutOfBounds(r);
        }
        if (c <= 0)
        {
            throw OutOfBounds(c);
        }
        rows = r;
        cols = c;
        pa = new T *[rows];
        for (int i = 0; i < rows; i++)
        {
            pa[i] = new T[cols];
        }
    }
    UnsignedIntArray(const UnsignedIntArray &arr);

    // Деструктор
    ~UnsignedIntArray()
    {
        for (int i = 0; i < rows; i++)
        {
            delete[] pa[i];
        }
        delete[] pa;
    }

    T *operator[](int index)
    {
        if (index < 0 || index >= rows)
        {
            throw OutOfBounds(index);
        }
        return pa[index];
    }

    // Геттери
    int getRows() const { return rows; };
    int getCols() const { return cols; };
};

template <typename T>
UnsignedIntArray<T>::UnsignedIntArray(const UnsignedIntArray &arr)
{
    rows = arr.rows;
    cols = arr.cols;
    pa = new T *[rows];
    for (int i = 0; i < rows; i++)
    {
        pa[i] = new T[cols];
        for (int j = 0; j < cols; j++)
        {
            pa[i][j] = arr.pa[i][j];
        }
    }
}

template <typename T>
T getMin(UnsignedIntArray<T> &a)
{
    UnsignedIntArray<T> res(a.getCols(), a.getRows());

    T min = a[0][0];

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            if (a[i][j] < min)
            {
                min = a[i][j];
            }
        }
    }
    return min;
}

template <typename T>
UnsignedIntArray<T> getx3(UnsignedIntArray<T> a)
{
    UnsignedIntArray<T> res(a.getCols(), a.getRows());

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            if (a[i][j] > 0)
            {
                res[i][j] = a[i][j] * 3;
            }
            else
            {
                res[i][j] = a[i][j];
            }
        }
    }

    return res;
}

#endif