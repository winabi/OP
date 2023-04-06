#include <iostream>
#include <fstream>

using namespace std;

// Ланка зв'язаного списку:
struct Link
{
    double data;
    Link *next;
};

// Функція зчитує зі вказаного файлу числа
// та повертає вказівник на нульовий елемент масиву.
// Масив створюється всередині функції, його елементи
// розташовуються в динамічній пам'яті
// Параметр count після завершення функції містить довжину масиву
double *readFromFile(const char *fileName, int &count)
{
    // Підготовка зв'язаного списку до роботи та створення файлового потоку:
    Link *first = 0;
    Link *last = 0;
    Link *link;
    ifstream in(fileName);
    double d;
    count = 0;      // лічильник чисел, які зчитані з файлу
    while (in >> d) // читання до кінця файлу
    {
        count++;
        // Створення нового елемента списку:
        link = new Link;
        link->data = d;
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
    // Створення й заповнення масиву чисел:
    double *arr = new double[count];
    link = first;
    for (int i = 0; i < count; i++)
    {
        arr[i] = link->data;
        link = link->next;
    }
    // Видалення з динамічної пам'яті елементів зв'язаного списку:
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
    int count = 0;
    double *arr = readFromFile("data.txt", count);
    int m = count;
    int res = count / 5;
    cout << res;
    // outToFile("results.txt", arr, count);
    delete[] arr;
    return 0;
}