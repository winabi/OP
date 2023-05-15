#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::for_each;
using std::istream;
using std::ostream;
using std::transform;
using std::vector;

class UnsignedIntArray
{
    friend ostream &operator<<(ostream &out, const UnsignedIntArray &a);
    friend istream &operator>>(istream &in, UnsignedIntArray &a);

    friend vector<vector<int>> operator+(const UnsignedIntArray &a, const UnsignedIntArray &b);
    friend vector<vector<int>> operator-(const UnsignedIntArray &a, const UnsignedIntArray &b);
    friend vector<vector<int>> operator*(const UnsignedIntArray &a, const UnsignedIntArray &b);

private:
    vector<vector<int>> data;
    int rows = 0;
    int cols = 0;

public:
    class OutOfBounds
    {
        int index;

    public:
        OutOfBounds(int i) : index(i) {}
        int getIndex() const { return index; }
    };

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

    vector<int> &operator[](int index)
    {
        if (index < 0 || index >= rows)
        {
            throw OutOfBounds(index);
        }
        return data[index];
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
};

UnsignedIntArray::UnsignedIntArray(const UnsignedIntArray &arr)
{
    rows = arr.rows;
    cols = arr.cols;
    data = arr.data;
}

vector<vector<int>> operator+(const UnsignedIntArray &a, const UnsignedIntArray &b)
{
    if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
    {
        throw std::invalid_argument("Matrices must have the same size");
    }

    int n = a.getRows();
    vector<vector<int>> result(n);
    for (int i = 0; i < n; i++)
    {
        result[i].resize(a.getCols());
        transform(a.data[i].begin(), a.data[i].end(), b.data[i].begin(), result[i].begin(), std::plus<int>());
    }
    return result;
}

vector<vector<int>> operator-(const UnsignedIntArray &a, const UnsignedIntArray &b)
{
    if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
    {
        throw std::invalid_argument("Matrices must have the same size");
    }

    int n = a.getRows();
    vector<vector<int>> result(n);
    for (int i = 0; i < n; i++)
    {
        result[i].resize(a.getCols());
        transform(a.data[i].begin(), a.data[i].end(), b.data[i].begin(), result[i].begin(), std::minus<int>());
    }
    return result;
}

vector<vector<int>> operator*(const UnsignedIntArray &a, const UnsignedIntArray &b)
{
    if (a.getCols() != b.getRows())
    {
        throw std::invalid_argument("Matrix dimensions are not compatible for multiplication");
    }

    int m = a.getRows();
    int n = a.getCols();
    int p = b.getCols();

    vector<vector<int>> result(m, vector<int>(p, 0));

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            for (int k = 0; k < n; k++)
            {
                result[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return result;
}

ostream &operator<<(ostream &out, const UnsignedIntArray &a)
{
    out << "\nArray:" << endl;
    for_each(a.data.begin(), a.data.end(), [&](const vector<int> &row)
             {
        for_each(row.begin(), row.end(), [&](int element) { out << element << " "; });
        out << endl; });
    return out;
}

istream &operator>>(istream &in, UnsignedIntArray &a)
{
    cout << "Please enter the elements of the array, row by row:" << endl;
    for (int i = 0; i < a.getRows(); i++)
    {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j < a.getCols(); j++)
        {
            in >> a.data[i][j];
            cout << a.data[i][j] << " ";
        }
        cout << endl;
    }
    return in;
}

void getLog10(UnsignedIntArray &a)
{
    for (int i = 0; i < a.getRows(); i++)
    {
        for (int j = 0; j < a.getCols(); j++)
        {
            if (a[i][j] > 0)
            {
                a[i][j] = log10(a[i][j]);
            }
        }
    }
}

int main()
{
    UnsignedIntArray a(2, 2);
    cin >> a;
    cout << "Matrix a:" << a << endl;

    UnsignedIntArray b(2, 2);
    cin >> b;
    cout << "Matrix b:" << b << endl;

    try
    {
        vector<vector<int>> cplus = a + b;
        cout << "Matrix a + b:" << endl;
        for_each(cplus.begin(), cplus.end(), [&](const vector<int> &row)
                 {
                     for_each(row.begin(), row.end(), [&](int element) { cout << element << " "; });
                     cout << endl; });

        vector<vector<int>> cminus = a - b;
        cout << "Matrix a - b:" << endl;
        for_each(cminus.begin(), cminus.end(), [&](const vector<int> &row)
                 {
                     for_each(row.begin(), row.end(), [&](int element) { cout << element << " "; });
                     cout << endl; });

        vector<vector<int>> cmult = a * b;
        cout << "Matrix a * b:" << endl;
        for_each(cmult.begin(), cmult.end(), [&](const vector<int> &row)
                 {
                     for_each(row.begin(), row.end(), [&](int element) { cout << element << " "; });
                     cout << endl; });
    }
    catch (const std::invalid_argument &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    getLog10(a);
    cout << "Matrix a after applying log10: " << a << endl;

    return 0;
}
