#include <iostream>
#include <math.h>
#include "lib.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;

template <typename T>
void cout_for_array(T *arr, int size, string message)
{
    cout << message << ": ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    const int size = 5;

    int arr1[size] = {22, 11, 323, 3, 12132};
    double arr2[size] = {0.21, 1.111, 2.0, 8.4, 0.5};
    string arr3[size] = {"lal", "lol", "awe", "was", "waf"};

    cout << "Our arrrays:\n";
    cout_for_array<int>(arr1, size, "Int array: ");
    cout_for_array<double>(arr2, size, "Double array: ");
    cout_for_array<string>(arr3, size, "String array: ");

    try
    {
        cout << "\nTask 1: swap parts with the specified indexes." << endl;
        swap_parts<int>(arr1, size, 1, 2);
        swap_parts<double>(arr2, size, 2, 3);
        swap_parts<string>(arr3, size, 0, 3);

        cout << "\nTask 2: search for an element with a certain value" << endl;
        cout << "323: " << find_element<int>(arr1, 323, size) << "\n";
        cout << "2.0: " << find_element<double>(arr2, 2.0, size) << "\n";
        cout << "was: " << find_element<string>(arr3, "was", size) << "\n";

        cout << "\nTask 3: swap all pairs of adjacent parts (with an even and odd index)." << endl;
        swap_couples<int>(arr1, size);
        swap_couples<double>(arr2, size);
        swap_couples<string>(arr3, size);
    }
    catch (int a)
    {
        if (a == -1)
        {
            cout << "ERROR: Element not found in the array" << endl;
        }
        else if (a == -2)
        {
            cout << "ERROR: To swap elements, the starting index must be smaller than the ending index" << endl;
        };
    }

    cout << "\nOur arrrays after all the tasks:\n";
    cout_for_array<int>(arr1, size, "Int array: ");
    cout_for_array<double>(arr2, size, "Double array: ");
    cout_for_array<string>(arr3, size, "String array: ");

    return 0;
}