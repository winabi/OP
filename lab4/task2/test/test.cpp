#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::transform;
using std::vector;

// Клас для представлення 2го масиву
class UnsignedIntArray
{
    // Дружні функції перевантаження операцій виведення та введення:
    friend ostream &operator<<(ostream &out, const UnsignedIntArray &a);
    friend istream &operator>>(istream &in, UnsignedIntArray &a);

    friend UnsignedIntArray operator+(const UnsignedIntArray &a, const UnsignedIntArray &b);
    friend UnsignedIntArray operator-(const UnsignedIntArray &a, const UnsignedIntArray &b);
    friend UnsignedIntArray operator*(const UnsignedIntArray &a, const UnsignedIntArray &b);

private:
    vector<vector<int>> data;
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

        data.resize(rows, vector<int>(cols, 0));
    }
    UnsignedIntArray(const UnsignedIntArray &arr);

    // Деструкторы нам не требуются

    // Перевантаження оператора []
    vector<int> &operator[](int index)
    {
        if (index < 0 || index >= rows)
        {
            throw OutOfBounds(index);
        }
        return data[index];
    }

    // Геттери
    int getRows() const { return rows; };
    int getCols() const { return cols; };
};

// Конструктор копіювання
UnsignedIntArray::UnsignedIntArray(const UnsignedIntArray &arr)
{
    rows = arr.rows;
    cols = arr.cols;
    data = arr.data; // Оператор присваивания для копирования существующего вектора
}

// Перевантажена операція додавання
UnsignedIntArray operator+(const UnsignedIntArray &a, const UnsignedIntArray &b)
{
    if (a.rows != b.rows || a.cols != b.cols)
    {
        throw std::invalid_argument("Matrices must have the same size");
    }

    int n = a.size();
    vector<vector<int>> result(n);
    for (int i = 0; i < a.rows; i++)
    {
        transform(a.data[i].begin(), a.data[i].end(), b.data[i].begin(), result.data[i].begin(), std::plus<int>());
    }
    return result;
}

// Перевантажена операція віднімання
UnsignedIntArray operator+(const UnsignedIntArray &a, const UnsignedIntArray &b)
{
    if (a.rows != b.rows || a.cols != b.cols)
    {
        throw std::invalid_argument("Matrices must have the same size");
    }

    int n = a.size();
    vector<vector<int>> result(n);
    for (int i = 0; i < a.rows; i++)
    {
        transform(a.data[i].begin(), a.data[i].end(), b.data[i].begin(), result.data[i].begin(), std::minus<int>());
    }
    return result;
}

// Перевантажена операція множення
UnsignedIntArray operator+(const UnsignedIntArray &a, const UnsignedIntArray &b)
{
    if (a.rows != b.rows || a.cols != b.cols)
    {
        throw std::invalid_argument("Matrices must have the same size");
    }

    int n = a.size();
    vector<vector<int>> result(n);
    for (int i = 0; i < a.rows; i++)
    {
        transform(a.data[i].begin(), a.data[i].end(), b.data[i].begin(), result.data[i].begin(), std::multiplies<int>());
    }
    return result;
}

// Перевантажена операція виведення в потік
ostream &operator<<(ostream &out, const UnsignedIntArray &a)
{
    out << "\nArray:" << endl;
    for_each(a.data.begin(), a.data.end(), [&](const vector<int> &row) { // data это вектор векторов, а - объект
        for_each(row.begin(), row.end(), [&](int element)
                 { out << element << " "; });
        out << endl;
    });
    return out;
}

// Перевантажена операція читання з потоку
istream &operator>>(istream &in, UnsignedIntArray &a)
{
    cout << "Please enter the elements of the array, row by row:" << endl;
    for (int i = 0; i < a.rows; i++)
    {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < a.cols; j++)
        {
            in >> a.data[i][j];
            cout << a.data[i][j] << " ";
        }
        cout << endl;
    }
    return in;
}

void getLog10(UnsignedIntArray &a) // викликаємо конструктор копіювання
{

    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            if (a.data[i][j] > 0)
            {
                a.data[i][j] = log10(a.data[i][j]);
            }
        }
    }
}

int main()
{
    UnsignedIntArray a(2, 2); // создали матрицу размером 2x2
    cin >> a;                 // считали значения элементов матрицы

    cout << "Matrix a:" << a << endl;

    // Выполняем операции с матрицами
    UnsignedIntArray b(2, 2);
    cin >> b; // Считываем матрицу b
    cout << "Matrix b:" << b << endl;

    try
    {

        UnsignedIntArray cplus = a + b;
        cout << "Matrix a + b:" << cplus << endl;

        UnsignedIntArray cminus = a - b;
        cout << "Matrix a - b:" << cminus << endl;

        UnsignedIntArray cmult = a * b;
        cout << "Matrix a * b:" << cmult << endl;
    }
    catch (UnsignedIntArray::OutOfBounds &e)
    {
        cout << "Error! Index " << e.getIndex() << " outside the array's boundaries." << endl;
    }
    catch (std::invalid_argument &e)
    {
        cout << "Error! " << e.what() << endl;
    }
    catch (...)
    {
        cout << "Unknown error!" << endl;
    }

    // Вызываем функцию для замены положительных элементов на логарифмы
    getLog10(a);

    // Выводим измененную матрицу
    cout << "Matrix a after replacing positive elements by logarithms:" << a << endl;

    try
    {
        // Проверяем границы индексов
        cout << "a[2][2] = " << a[2][2] << endl; // Ошибка! Выход за границы массива
    }
    catch (UnsignedIntArray::OutOfBounds &e)
    {
        cout << "Error! Index " << e.getIndex() << " outside the array's boundaries." << endl;
    }
    catch (...)
    {
        cout << "Unknown error!" << endl;
    }

    try
    {
        // Создаем матрицу с неверными параметрами
        UnsignedIntArray d(-1, 3); // Ошибка! Неверный размер массива
    }
    catch (UnsignedIntArray::OutOfBounds &e)
    {
        cout << "Error when creating a matrix! The number of array elements cannot be: " << e.getIndex() << "." << endl;
    }
    catch (...)
    {
        cout << "Unknown error!" << endl;
    }

    return 0;
}
