#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::strcpy;
using std::strlen;

const int MAX_COUNT = 50; // Максимальна кількість студентів у группі

// Треба заздалегідь оголосити клас, щоб можна було створювати вказівник:
class Group;

// Клас для представлення міста
class Student
{
    // Перевантажений оператор для виведення в потік
    friend std::ostream &operator<<(std::ostream &out, const Student &student);

private:
    unsigned int IDNumber;   // Номер студентського посвідчення
    char *surname = nullptr; // прізвище, яке виділено у дінамічній пам'яті
    int *myArray;
    int arraySize = 0;
    Group *group = nullptr; // вказівник на групу

public:
    // Конструктори:
    Student() {}
    Student(unsigned int IDNumber, const char *surname, int *myArray, int arraySize, Group *group);
    Student(const Student &student);

    ~Student()
    {
        delete[] myArray; // звільняємо виділену пам'ять для масиву
    }

    void fillArray()
    {
        for (int i = 0; i < arraySize; i++)
        {
            myArray[i] = i + 1;
        }
    }

    // Геттери:
    unsigned int getIDNumber() const { return IDNumber; }
    const char *getSurname() const { return surname; };
    int *getArray() const { return myArray; }
    int getArraySize() const { return arraySize; }
    Group *getGroup() const { return group; }

    // Сеттери:
    void setIDNumber(unsigned int number) { IDNumber = number; }
    void setSurname(const char *surname)
    {
        if (this->surname != nullptr) // перевірка наявності попереднього значення прізвища
        {
            delete[] this->surname; // звільнення пам'яті, виділеної для попереднього значення
        }
        this->surname = new char[strlen(surname) + 1]; // виділення пам'яті для зберігання нового значення прізвища
        strcpy(this->surname, surname);                // копіювання значення прізвища у виділену пам'ять
    }
    void setMyArray(int *array, int size)
    {
        arraySize = size;
        myArray = new int[size];
        for (int i = 0; i < size; i++)
        {
            myArray[i] = array[i];
        }
    }
    void setGroup(Group *group) { this->group = group; }

    // Перевантажена операція присвоєння
    const Student &operator=(const Student &student);
};

// Конструктор з параметрами, реалізований через виклик сеттерів
Student::Student(unsigned int IDNumber, const char *surname, int *myArray, int arraySize, Group *group)
{
    setIDNumber(IDNumber);
    setSurname(surname);
    setMyArray(myArray, arraySize);
    setGroup(group);
}

// Конструктор копіювання
Student::Student(const Student &student)
{
    IDNumber = student.IDNumber;

    // Виділяємо пам'ять для нового рядка та копіюємо значення з оригінального рядка
    surname = new char[strlen(student.surname) + 1];

    strcpy(surname, student.surname);
    // Виділяємо пам'ять для нового масиву та копіюємо значення з оригінального масиву
    arraySize = student.arraySize;
    myArray = new int[arraySize];
    for (int i = 0; i < arraySize; i++)
    { // копіюємо значення з оригінального масиву
        myArray[i] = student.myArray[i];
    }
    group = student.group;

    // Присвоюємо вказівник на ту саму групу, що й у оригінальному об'єкті
    IDNumber = student.IDNumber;
}

class Group
{
    // Перевантажений оператор для виведення в потік
    friend std::ostream &operator<<(std::ostream &out, const Group &group)
    {
        out << "Group Index: " << group.groupIndex << "\n\n";
        for (int i = 0; i < group.count; i++)
        {
            out << *(group.student[i]) << endl;
        }
        out << endl;
        return out;
    }

private:
    Student *student[MAX_COUNT] = {}; // масив указівників на студентів
    unsigned int groupIndex;          // індекс групи
    int count = 0;                    // кількість вказівників у масиві
public:
    // Конструктори:
    Group() {}
    Group(unsigned int groupIndex) { setGroupIndex(groupIndex); }

    // Геттер
    const char getGroupIndex() const { return groupIndex; }

    // Сеттери:
    void setGroupIndex(unsigned int Index) { groupIndex = Index; }
    void setGroups(Student *student[], int count);

    // Перевантажена операція присвоєння
    const Group &operator=(const Group &group);

    // Сортування за фамілією
    void sortBySurname();

    // Вивід за ознакою
    void printIf();

    // перевантаження операції отримання елемента за індексом
    Student &operator[](int index)
    {
        return *student[index];
    }
};

// Отримаємо з параметру й заповнюємо масив студентів
void Group::setGroups(Student *student[], int count)
{
    this->count = count;
    for (int i = 0; i < count; i++)
    {
        this->student[i] = student[i];
        this->student[i]->setGroup(this); // this позволяет получить доступ к текущему объекту класса Group.
                                          //  Затем вызывается метод setGroup() [который находитя у объекта класса Student],
                                          //  передавая ему указатель на текущий объект класса Group, чтобы установить связь между объектами Group и Students
    }
}

// Сортировка по фамилии
void Group::sortBySurname()
{
    bool mustSort;
    do
    {
        mustSort = false;
        for (int i = 0; i < count - 1; i++)
        {
            if (strcmp(student[i]->getSurname(), student[i + 1]->getSurname()) > 0)
            {
                Student *temp = student[i];
                student[i] = student[i + 1];
                student[i + 1] = temp;
                mustSort = true;
            }
        }
    } while (mustSort);
}

std::ostream &operator<<(std::ostream &out, const Student &student)
{
    char buffer[300];
    sprintf(buffer, "ID: %u\nSurname: %s\nArray: \n", student.IDNumber, student.surname);

    for (int i = 0; i < student.arraySize; i++)
    {
        sprintf(buffer + strlen(buffer), "%d ", student.myArray[i]);
        // buffer + strlen(buffer)получние указателя на позицию в буфере, которая находится после последнего записанного символа
        //(с помощью strlen(buffer) мы получаем длину строки, которую уже записали в буфер, и к указателю buffer прибавляем эту длину).
        //  buffer указывает на первый элемент массива
    }

    sprintf(buffer + strlen(buffer), "\n");
    out << buffer;
    return out;
}

void Group::printIf()
{
    for (int i = 0; i < count; i++)
    {
        if ((student[i]->getIDNumber()) % 2 != 0)
        {
            cout << *student[i];
        }
    }
}

int main()
{
    setlocale(LC_ALL, "UKRAINIAN");
    const int realCount = 4;     // працюємо з чотирма студентами
    Student *student[realCount]; // створюємо масив вказівників на студентів

    // заповнюємо масив
    int tempArray[] = {100, 100, 100, 100, 100, 100, 100, 100};

    student[0] = new Student(1421125, "Іванів", tempArray, 8, nullptr);
    student[1] = new Student(284942, "Кучма", tempArray, 8, nullptr);
    student[2] = new Student(54618, "Константінов", tempArray, 8, nullptr);
    student[3] = new Student(264753, "Григор'єва", tempArray, 8, nullptr);

    Group group = 211432;

    group.setGroups(student, realCount);
    cout << "Display the group data: \n"
         << group << "\n\n"; // виводимо всі дані
    cout << "Display information about the student by index: \n"
         << *student[0] << "\n\n";
    group.sortBySurname();
    cout << "Display all data after sorting\n"
         << group << "\n\n";

    cout << "Remove students with odd student ID numbers:"
         << "\n\n";
    group.printIf();

    // Видалення студентів, на які вказують вказівники в масиві student
    for (int i = 0; i < realCount; i++)
    {
        delete student[i];
    }

    return 0;
}
