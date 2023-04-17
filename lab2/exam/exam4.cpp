#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

// Клас для представлення одновимірного масиву
class IntArray
{
    // Дружні функції перевантаження операцій виведення та введення:
    friend ostream &operator<<(ostream &out, const IntArray &a);
    friend istream &operator>>(istream &in, IntArray &a);

private:
    int *pa = nullptr; // вказівник на майбутній масив
    int size = 0;      // поточний розмір масиву
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
    IntArray() {}
    IntArray(int n) { pa = new int[size = n]; }
    IntArray(IntArray &arr);

    ~IntArray();                // деструктор
    void addElem(int elem);     // функція додавання елемента
    int &operator[](int index); // доступ до елементів за читанням і записом

    // Перевантажені операції:
    const IntArray &operator=(const IntArray &a);
    bool operator==(const IntArray &a) const;

    int getSize() const { return size; } // повертає кількість елементів масиву
};

// Перевантажена операція виведення в потік
ostream &operator<<(ostream &out, const IntArray &a)
{
    for (int i = 0; i < a.size; i++)
    {
        out << a.pa[i] << ' ';
    }
    return out;
}

// Перевантажена операція читання з потоку
istream &operator>>(istream &in, IntArray &a)
{
    for (int i = 0; i < a.size; i++)
    {
        in >> a.pa[i];
    }
    return in;
}

// Конструктор копіювання
IntArray::IntArray(IntArray &arr)
{
    size = arr.size;
    pa = new int[size];
    for (int i = 0; i < size; i++)
    {
        pa[i] = arr.pa[i];
    }
}

// Деструктор
IntArray::~IntArray()
{
    if (pa != nullptr)
    {
        delete[] pa;
    }
}

// Додавання елемента. Розташування масиву на новому місці
void IntArray::addElem(int elem)
{
    int *temp = new int[size + 1];
    if (pa != nullptr)
    {
        for (int i = 0; i < size; i++)
        {
            temp[i] = pa[i];
        }
        delete[] pa;
    }
    pa = temp;
    pa[size] = elem;
    size++;
}

// Забезпечує доступ до елементів за читанням і записом
// Генерує виняток OutOfBounds у випадку хибного індексу
int &IntArray::operator[](int index)
{
    if (index < 0 || index >= size)
    {
        throw OutOfBounds(index);
    }
    return pa[index];
}

// Перевантажена операція присвоєння масиву елементів іншого
const IntArray &IntArray::operator=(const IntArray &a)
{
    if (&a != this)
    {
        if (pa != nullptr)
        {
            delete[] pa;
        }
        size = a.size;
        pa = new int[size];
        for (int i = 0; i < size; i++)
        {
            pa[i] = a.pa[i];
        }
    }
    return *this;
}

// Перевантажена операція порівняння масивів
bool IntArray::operator==(const IntArray &a) const
{
    if (&a == this)
    {
        return true;
    }
    if (size != a.size)
    {
        return false;
    }
    for (int i = 0; i < size; i++)
    {
        if (pa[i] != a.pa[i])
        {

            return false;
        }
    }
    return true;
}

// Глобальна функція знаходження мінімального елемента масиву
// Функція не має прямого доступу до даних и використовує
// перевантажені операції й функції-елементи
int getMin(IntArray a) // викликаємо конструктор копіювання
{
    int min = a[0];
    for (int i = 1; i < a.getSize(); i++)
    {
        if (min > a[i])
        {
            min = a[i];
        }
    }
    return min;
}

void main()
{
    setlocale(LC_ALL, "UKRAINIAN");
    IntArray a(2); // Масив з двох елементів
    cout << "Введiть два елементи масиву: ";
    cin >> a;
    cout << "Елементи масиву: " << a << endl;
    a.addElem(12);
    cout << "Додаємо елемент" << endl;
    cout << "Елементи масиву: " << a << endl;
    try
    {
        a[1] = 2;   // змінили
        a[10] = 35; // хибний індекс
    }
    catch (IntArray::OutOfBounds &e)
    {
        cout << "Хибний iндекс: " << e.getIndex() << endl;
    }
    cout << "Новi елементи: " << a << endl;
    IntArray b; // створили новий масив
    b = a;      // скопіювали елементи
    if (a == b)
    {
        cout << "Масиви a i b однаковi" << endl;
    }
    else
    {
        cout << "Масиви a i b різнi";
    }
    cout << "Мiнiмальний елемент: " << getMin(a) << endl;
}