#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

const int n = 5;

// Ланка зв'язаного списку:
struct Link
{
    double data;
    Link *next;
};

double **funcLab5Task1(double **arr, int m, int n)
{
    double **new_arr = new double *[m];
    for (int i = 0; i < m; i++)
    {
        new_arr[i] = new double[n];
        for (int j = 0; j < n; j++)
        {
            new_arr[i][j] = arr[i][j];
            if (new_arr[i][j] > 0)
            {
                new_arr[i][j] = log10(new_arr[i][j]);
            }
        }
    }
    return new_arr;
}

void funcLab5Task2(double **arr1, double *arr2, int m, int n)
{
    for (int i = 0; i < n; i++)
    {
        bool eq = false;
        arr2[i] = 0;

        for (int j = 0; j < m; j++)
        {
            if (arr1[j][i] < 0)
            {
                eq = true;
                arr2[i] += arr1[j][i];
            }
        }

        if (eq == false)
        {
            cout << "ERROR: no negative elements in the column " << i + 1 << ". The corresponding element in the second array will be 0." << endl;
        }
    }
}

double **create2DArray(int n, int m)
{
    double **arr = new double *[m];
    for (int i = 0; i < m; i++)
    {
        arr[i] = new double[n];
    }
    return arr;
}

double **readFromFile(const char *fileName, int &count, int n, int &m)
{
    Link *first = 0;
    Link *last = 0;
    Link *link;

    ifstream in(fileName);

    int i;
    count = 0;

    while (in >> i)
    {
        count++;

        link = new Link;
        link->data = i;
        link->next = 0;

        if (last == 0)
        {
            first = link;
        }
        else
        {
            last->next = link;
        }

        last = link;
    }

    m = count / n;

    double **arr = new double *[m];
    link = first;

    for (int i = 0; i < m; i++)
    {
        arr[i] = new double[n];

        for (int j = 0; j < n; j++)
        {
            if (link)
            {
                arr[i][j] = link->data;
                link = link->next;
            }
        }
    }

    // вывод массива arr
    // for (int i = 0; i < m; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         cout << arr[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    while (first)
    {
        link = first;
        first = first->next;
        delete link;
    }

    return arr;
}

// Записує елементи масиву arr довжини count
// у вказаний текстовий файл

// Записує елементи масиву arr довжини count
// у вказаний текстовий файл
void outToFile(const char *filename, double *arr, int count)
{
    ofstream out(filename);
    for (int i = count - 1; i >= 0; i--)
    {
        out << arr[i] << " ";
    }
}

int main()
{
    // lab5
    int count = 0;
    int m = 0;
    double arr2{};

    // Первоначальный массив
    double **arr = readFromFile("data.txt", count, n, m);

    // Для заданий
    const int m2 = m;

    // Задание 1
    double **arr1 = create2DArray(n, m);
    arr1 = funcLab5Task1(arr, m, n);

    // Задание 2
    double *arr2 = new double[n];
    funcLab5Task2(arr1, arr2, m, n);

    // Вывод результатов в файл
    outToFile("results.txt", arr2, n);

    // Освобождение памяти
    for (int i = 0; i < m; i++)
    {
        delete[] arr1[i];
    }
    delete[] arr1;
    delete[] arr2;

    for (int i = 0; i < m; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    return 0;
}
