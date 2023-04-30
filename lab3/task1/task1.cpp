#pragma warning(disable : 4996)
#include <cstring>
#include <iostream>

using std::strcpy;

using std::cout;
using std::endl;

class Human
{
private:
    char name[30];
    int age;
    char occupation[10];

public:
    Human(const char *name, double age)
    {
        strcpy(this->name, name);
        this->age = age;
        strcpy(this->occupation, occupation);
    }

    char *getName()
    {
        return name;
    }
    int getAge() const
    {
        return age;
    }
    char *getOccupation()
    {
        return occupation;
    }

    virtual void show()
    {
        cout << endl
             << "Name: " << name << "\tAge: " << age;
    }
};
class Citizen : public Human
{
private:
    char country[30];

public:
    Citizen(const char *name, int age, char *country)
        : Human(name, age) { strcpy(this->country, country); }

    char *getOccupation()
    {
        return country;
    }

    void show()
    {
        Human::show();
        cout << "\tCountry: " << country;
    }
};

class Student : public Citizen
{
private:
    char group[30];

public:
    Student(const char *name, int age, char *country, char *group)
        : Citizen(name, age, country) { strcpy(this->group, group); }

    char *getGroup()
    {
        return group;
    }

    void show()
    {
        Human::show();
        cout << "\tGroup: " << group;
    }
};

class Employee : public Citizen
{
private:
    char job[30];

public:
    Employee(const char *name, int age, char *country, char *job)
        : Citizen(name, age, country) { strcpy(this->job, job); }

    char *getJob()
    {
        return job;
    }

    void show()
    {
        Human::show();
        cout << "\tJob: " << job;
    }
};

int main()
{
    setlocale(LC_ALL, "UKRAINIAN");
    const int N = 4;

    Human *humans[N] = {
        new Student("Іванів", 17, "Україна", "222В"),
        new Citizen("Кучма", 18, "Україна"),
        new Employee("Константинів", 18, "Україна", "Програміст"),
        new Human("Григор'єва", 19),
    };

    for (int i = 0; i < N; i++)
    {
        humans[i]->show();
    }
    cout << endl;

    for (int i = 0; i < N; i++)
    {
        delete humans[i];
    }

    return 0;
}