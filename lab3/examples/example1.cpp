#pragma warning(disable : 4996)

#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::strcpy;

class Region
{
private:
    char name[30];
    double area;

public:
    Region(const char *name, double area)
    {
        strcpy(this->name, name);
        this->area = area;
    }
    char *getName()
    {
        return name;
    }
    double getArea() const
    {
        return area;
    }
    virtual void show()
    {
        cout << endl
             << "Назва: " << name << ".\tПлоща: " << area << " кв.км.";
    }
    virtual ~Region() {}
};

class PopulatedRegion : public Region
{
private:
    int population;

public:
    PopulatedRegion(const char *name, double area, int population)
        : Region(name, area) { this->population = population; }
    int getPopulation() const
    {
        return population;
    }
    double density() const
    {
        return population / getArea();
    }
    void show() override
    {
        Region::show();
        cout << "\tНаселення:" << population << " чол.\tЩiльнiсть: " << density() << " чол/кв.км.";
    }
};

class Country : public PopulatedRegion
{
private:
    char capital[20];

public:
    Country(const char *name, double area, int population, const char *capital)
        : PopulatedRegion(name, area, population) { strcpy(this->capital, capital); }

public:
    char *getCapital()
    {
        return capital;
    }
    void show() override
    {
        PopulatedRegion::show();
        cout << "\tСтолиця " << capital;
    }
};

class City : public PopulatedRegion
{
private:
    int boroughs;

public:
    City(const char *name, double area, int population, int boroughs)
        : PopulatedRegion(name, area, population) { this->boroughs = boroughs; }

public:
    int getBoroughs() const
    {
        return boroughs;
    }
    void show() override
    {
        PopulatedRegion::show();
        cout << "\tРайонiв: " << boroughs;
    }
};

class Island : public PopulatedRegion
{
private:
    char sea[30];

public:
    Island(const char *name, double area, int population, const char *sea)
        : PopulatedRegion(name, area, population) { strcpy(this->sea, sea); }
    char *getSea()
    {
        return sea;
    }
    virtual void show() override
    {
        PopulatedRegion::show();
        cout << "\tМоре: " << sea;
    }
};

void main()
{
    setlocale(LC_ALL, "UKRAINIAN");
    const int N = 4;
    Region *regions[N] = {
        new City("Київ", 839, 2679000, 10),
        new Country("Україна", 603700, 46294000, "Київ"),
        new City("Харкiв", 310, 1461000, 9),
        new Island("Змiїний", 0.2, 30, "Чорне")};
    for (int i = 0; i < N; i++)
    {
        regions[i]->show();
    }
    for (int i = 0; i < N; i++)
    {
        delete regions[i];
    }
}