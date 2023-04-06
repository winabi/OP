#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

const int n = 5;

struct Link
{
    double data;
    Link *next;
};

int **func1(int **arr, int m, int n)
{
    int **arr1 = new int *[m];
    for (int i = 0; i < m; i++)
    {
        arr1[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            arr1[i][j] = arr[i][j];
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr1[i][j] > 0)
            {
                arr1[i][j] = log10(arr[i][j]);
            }
        }
    }

    return arr1;
}

void func2(const char *filename, int **arr1, int *arr2, int m, int n)
{
    ofstream out(filename);
    int text = 0;

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
            if (text == 0)
            {
                out << "Error output during function 2: " << endl;
                text = 1;
            }

            out << "ERROR: no negative elements in the column " << i + 1 << ". The corresponding element in the second array will be 0." << endl;
        }
    }
    out.close();
}

int **readFromFile(const char *fileName, int &count, int n, int &m)
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

    int **arr = new int *[m];
    link = first;

    for (int i = 0; i < m; i++)
    {
        arr[i] = new int[n];

        for (int j = 0; j < n; j++)
        {
            if (link)
            {
                arr[i][j] = link->data;
                link = link->next;
            }
        }
    }

    while (first)
    {
        link = first;
        first = first->next;
        delete link;
    }

    return arr;
}

void outToFile(const char *filename, int **arr, int **arr1, int *arr2, int n, int m, int count)
{
    ofstream out(filename, ios::app);

    out << "\nArray:" << endl;
    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < n; j++)

        {

            out << arr[i][j] << "\t";
        }

        out << "\n";
    }

    out << "\nArray after executing func1:" << endl;
    for (int i = 0; i < m; i++)
    {

        for (int j = 0; j < n; j++)

        {

            out << arr1[i][j] << "\t";
        }

        out << "\n";
    }

    out << "\nArray after executing func2:" << endl;

    for (int i = 0; i < n; i++)
    {
        out << arr2[i] << "\t";
    }
}

int main()
{
    int count = 0;
    int m = 0;

    int **arr = readFromFile("data.txt", count, n, m);

    // TASK1 lab 4
    int **arr1 = func1(arr, m, n);

    // TASK2 lab 4
    int *arr2 = new int[n];
    func2("results.txt", arr1, arr2, m, n);

    // output
    outToFile("results.txt", arr, arr1, arr2, n, m, count);

    // Освобождение памяти
    for (int i = 0; i < m; i++)
    {
        delete[] arr[i];
    }
    delete[] arr;

    for (int i = 0; i < m; i++)
    {
        delete[] arr1[i];
    }
    delete[] arr1;

    delete[] arr2;

    return 0;
}