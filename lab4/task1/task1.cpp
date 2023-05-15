#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <queue>

using std::cout;
using std::endl;
using std::priority_queue;
using std::string;
using std::vector;

const int MAX_COUNT = 50; // Максимальна кількість студентів у группі

// Треба заздалегідь оголосити клас, щоб можна було створювати вказівник:
class Group;

// Клас для представлення міста
class Student
{
    // Перевантажений оператор для виведення в потік
    friend std::ostream &operator<<(std::ostream &out, const Student &student);

private:
    unsigned int IDNumber; // Номер студентського посвідчення
    string surname;        // прізвище, яке виділено у дінамічній пам'яті
    vector<int> myArray;
    Group *group = nullptr; // вказівник на групу

public:
    // Конструктори:
    Student() {}
    Student(unsigned int IDNumber, const string surname, const vector<int> &myArray, Group *group);
    Student(const Student &student);

    // Геттери:
    unsigned int getIDNumber() const { return IDNumber; }
    const string &getSurname() const { return surname; }
    const vector<int> getArray() const
    {
        return myArray;
    }
    Group *getGroup() const { return group; }

    // Сеттери:
    void setIDNumber(unsigned int number) { IDNumber = number; }
    void setSurname(const string &surname)
    {
        if (!this->surname.empty()) // перевірка наявності попереднього значення прізвища
        {
            this->surname.clear(); // звільнення пам'яті, виділеної для попереднього значення
        }
        this->surname = surname; // присваивание нового значения фамилии
    }
    void setMyArray(const vector<int> &array)
    {
        myArray = array;
    }
    void setGroup(Group *group) { this->group = group; }

    // Перевантажена операція присвоєння
    const Student &operator=(const Student &student);

    double calculateIndicator() const
    {
        double sum = 0;
        for (int i = 0; i < myArray.size(); i++)
        {
            sum += myArray[i];
        }
        return sum / myArray.size(); // Средняя оценка студента
    }
};

// Конструктор з параметрами, реалізований через виклик сеттерів
Student::Student(unsigned int IDNumber, const string surname, const vector<int> &myArray, Group *group)
{
    setIDNumber(IDNumber);
    setSurname(surname);
    setMyArray(myArray);
    setGroup(group);
}

// Конструктор копіювання
Student::Student(const Student &student)
{
    IDNumber = student.IDNumber;
    surname = student.surname;
    myArray = student.myArray;
    group = student.group;
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
    vector<Student *> student;
    unsigned int groupIndex; // індекс групи
    int count = 0;           // кількість вказівників у масиві

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

    // Вивід за ознакою
    void printIf();

    // перевантаження операції отримання елемента за індексом
    Student &operator[](int index)
    {
        return *student[index];
    }

    static bool sortByIndicator(const Student *s1, const Student *s2)
    {
        return s1->calculateIndicator() < s2->calculateIndicator();
    }

    void sortStudentsByIndicator()
    {
        sort(student.begin(), student.end(), sortByIndicator);
    }

    ~Group()
    {
        for (const auto &student : student)
        {
            delete student;
        }
    }
};

// Отримаємо з параметру й заповнюємо масив студентів
void Group::setGroups(Student *student[], int count)
{
    this->count = count;
    for (int i = 0; i < count; i++)
    {
        this->student.push_back(student[i]);
        this->student[i]->setGroup(this); // this позволяет получить доступ к текущему объекту класса Group.
                                          //  Затем вызывается метод setGroup() [который находитя у объекта класса Student],
                                          //  передавая ему указатель на текущий объект класса Group, чтобы установить связь между объектами Group и Students
    }
}

std::ostream &operator<<(std::ostream &out, const Student &student)
{
    out << "ID: " << student.IDNumber << "\n"; // out это поток
    out << "Surname: " << student.surname << "\n";
    out << "Array: ";

    for (const auto &value : student.myArray)
    {
        out << value << " ";
    }

    out << "\n";

    return out;
}

void Group::printIf()
{
    for_each(
        student.begin(), student.end(), [this](const Student *s) // this для доступа к переменной student
        {
        if ((s->getIDNumber()) % 2 != 0)
            {
                cout << *s << endl;
            } });
}

int main()
{
    setlocale(LC_ALL, "UKRAINIAN");
    const int realCount = 4;     // працюємо з чотирма студентами
    Student *student[realCount]; // створюємо масив вказівників на студентів

    // заповнюємо масив
    vector<int> tempArray = {100, 100, 100, 100, 100, 100, 100, 100};

    student[0] = new Student(1421125, "Іванів", tempArray, nullptr);
    student[1] = new Student(284942, "Кучма", tempArray, nullptr);
    student[2] = new Student(54618, "Константінов", tempArray, nullptr);
    student[3] = new Student(264753, "Григор'єва", tempArray, nullptr);

    Group group = 211432;
    group.setGroups(student, realCount);

    // Создаем очередь с приоритетом для хранения студентов
    priority_queue<Student *, vector<Student *>, decltype(&Group::sortByIndicator)> studentPriorityQueue(&group.sortByIndicator);

    // Добавляем студентов в очередь с приоритетом
    for (int i = 0; i < realCount; i++)
    {
        studentPriorityQueue.push(student[i]);
    }

    // Выводим данные группы перед сортировкой
    cout << "Display the group data: \n"
         << group << "\n\n";

    // Выводим информацию о студенте по индексу
    cout << "Display information about the student by index: \n"
         << *student[0] << "\n\n";

    // Сортируем студентов в группе по среднему баллу
    group.sortStudentsByIndicator();

    // Выводим данные группы после сортировки
    cout << "Display all data after sorting\n"
         << group << "\n\n";

    // Выводим студентов с нечетными номерами студенческого билета
    cout << "Remove students with odd student ID numbers:"
         << "\n\n";
    group.printIf();

    // Выводим студентов из очереди с приоритетом в порядке убывания среднего балла
    cout << "Display all data from priority queue:"
         << "\n\n";
    while (!studentPriorityQueue.empty())
    {
        cout << *studentPriorityQueue.top() << endl;
        studentPriorityQueue.pop();
    }

    return 0;
}
