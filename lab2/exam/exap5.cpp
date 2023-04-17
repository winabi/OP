#include <iostream>
using std::cout;
using std::endl;

class ObjectCount
{
private:
    static int count;

public:
    static int getCount()
    {
        return count;
    }
    ObjectCount()
    {
        count++;
    }
    ~ObjectCount()
    {
        count--;
    }
};

// Статичний елемент даних слід визначити й ініціалізувати поза межами класу:
int ObjectCount::count = 0;

void main()
{
    ObjectCount c1;
    cout << c1.getCount() << endl;  // 1
    ObjectCount *p1 = &c1;          // копіюємо адресу, конструктор не викликається
    cout << p1->getCount() << endl; // 1
    ObjectCount *p2 = new ObjectCount();
    cout << p2->getCount() << endl; // 2
    delete p2;
    cout << p2->getCount() << endl; // 1
}