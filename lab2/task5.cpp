#include <iostream>
using std::cout;
using std::endl;

class Counter
{
private:
    int x;
    static int count;

public:
    // Геттер
    int getX()
    {
        return x;
    }
    static int getCount()
    {
        return count;
    }

    Counter(int a)
    {
        x = a;
        count += x;
    }
};

// Статичний елемент даних слід визначити й ініціалізувати поза межами класу:
int Counter::count = 0;

int main()
{
    Counter c1(23);
    Counter c2(3);
    Counter c3(10);
    Counter c4(-10);

    cout << Counter::getCount() << endl;

    return 0;
}
