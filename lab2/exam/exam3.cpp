#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <iostream>

using std::cout;
using std::endl;
using std::strcpy;
using std::strlen;

const int MAX_COUNT = 100; // Максимальна кількість міст

// Треба заздалегідь оголосити клас, щоб можна було створювати вказівник:
class Country;

// Клас для представлення міста
class City
{
    // Перевантажений оператор для виведення в потік
    friend std::ostream &operator<<(std::ostream &out, const City &city);

private:
    char *name = nullptr;       // назва міста
    Country *country = nullptr; // вказівник на країну розташування
    char *region = nullptr;     // назва регіону
    int population = 0;         // населення
public:
    // Конструктори:
    City() {}
    City(const char *name, Country *country, const char *region, int population);
    City(const City &city);

    ~City(); // деструктор

    // Геттери:
    const char *getName() const { return name; }
    Country *getCountry() const { return country; }
    const char *getRegion() const { return region; }
    int getPopulation() const { return population; }

    // Сеттери:
    void setName(const char *name);
    void setRegion(const char *region);
    void setCountry(Country *country) { this->country = country; }
    void setPopulation(int population) { this->population = population; }

    // Перевантажена операція присвоєння
    const City &operator=(const City &city);
};

// Конструктор з параметрами, реалізований через виклик сеттерів
City::City(const char *name, Country *country, const char *region, int population)
{
    setName(name);
    setCountry(country);
    setRegion(region);
    setPopulation(population);
}

// Конструктор копіювання
City::City(const City &city)
{
    name = new char[strlen(city.name) + 1];
    strcpy(name, city.name);
    region = new char[strlen(city.region) + 1];
    strcpy(region, city.region);
    country = city.country;
    population = city.population;
}

// Видаляємо з пам'яті назви міста і регіону (якщо масиви створювалися)
City::~City()
{
    if (name != nullptr)
    {
        delete[] name;
    }
    if (region != nullptr)
    {
        delete[] region;
    }
}

// Видаляємо попередню назву міста, створюємо новий масив і записуємо нову назву
void City::setName(const char *name)
{
    if (this->name != nullptr)
    {
        delete[] this->name;
    }
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

// Видаляємо попередню назву регіону, створюємо новий масив і записуємо нову назву
void City::setRegion(const char *region)
{
    if (this->region != nullptr)
    {
        delete[] this->region;
    }
    this->region = new char[strlen(region) + 1];
    strcpy(this->region, region);
}

// Реалізуємо перевантажену операцію присвоєння через виклик сеттерів
const City &City::operator=(const City &city)
{
    if (&city != this)
    {
        setName(city.name);
        setCountry(city.country);
        setRegion(city.region);
        setPopulation(city.population);
    }
    return *this;
}

// Перевантажена операція порівняння двох міст
bool operator>(const City &c1, const City &c2)
{
    return c1.getPopulation() > c2.getPopulation();
}

// Клас для представлення країни
class Country
{
    // Перевантажений оператор для виведення в потік
    friend std::ostream &operator<<(std::ostream &out, const Country &country)
    {
        out << country.name << endl;
        for (int i = 0; i < country.count; i++)
        {
            out << *(country.cities[i]) << endl;
        }
        out << endl;
        return out;
    }

private:
    char name[40];                // назва країни
    City *cities[MAX_COUNT] = {}; // масив указівників на міста
    int count = 0;                // кількість вказівників у масиві
public:
    // Конструктори:
    Country() {}
    Country(const char *name) { setName(name); }

    const char *getName() const { return name; } // геттер

    // Перевантажений оператор для отримання елементів масиву
    City *operator[](int index) const { return cities[index]; }

    // Сеттери:
    void setName(const char *name) { strcpy(this->name, name); }
    void setStites(City *cities[], int count);

    void sortByPopulation(); // Сортування за населенням
};

// Отримаємо з параметру й заповнюємо масив міст
void Country::setStites(City *cities[], int count)
{
    this->count = count;
    for (int i = 0; i < count; i++)
    {
        this->cities[i] = cities[i];
        this->cities[i]->setCountry(this);
    }
}

// Сортування за населенням
void Country::sortByPopulation()
{
    bool mustSort = true; // повторюємо сортування
                          // якщо mustSort дорівнює true
    do
    {
        mustSort = false;
        for (int i = 0; i < count - 1; i++)
        {
            // Здійснюємо розіменування,
            // бо порівнювати можна об'єкти, а не вказівники:
            if (*(cities[i]) > *(cities[i + 1]))
            // Обмiнюємо елементи
            {
                City *temp = cities[i];
                cities[i] = cities[i + 1];
                cities[i + 1] = temp;
                mustSort = true;
            }
        }
    } while (mustSort);
}

// Перевантажений оператор для виведення в потік
std::ostream &operator<<(std::ostream &out, const City &city)
{
    char buffer[300];
    sprintf(buffer, "Мiсто: %s.\tКраїна: %s.\tРегiон: %s.\tНаселення: %d",
            city.name, city.country->getName(), city.region, city.population);
    out << buffer;
    return out;
}

// Допоміжна функція для заповнення масиву вказівників на міста
void createStites(City *cities[])
{
    cities[0] = new City("Харкiв", nullptr, "Харкiвська область", 1421125);
    cities[1] = new City("Полтава", nullptr, "Полтавська область", 284942);
    cities[2] = new City("Лозова", nullptr, "Харкiвська область", 54618);
    cities[3] = new City("Суми", nullptr, "Сумська область", 264753);
}

int main()
{
    setlocale(LC_ALL, "UKRAINIAN");
    const int realCount = 4;              // працюємо з чотирма містами
    City *cities[realCount];              // створюємо масив вказівників на міста
    createStites(cities);                 // заповнюємо масив
    Country country = "Україна";          // створюємо об'єкт "Країна",
                                          // викликаємо конструктор з одним параметром
    country.setStites(cities, realCount); // копіюємо міста в об'єкт "Країна"
    cout << country << endl;              // виводимо всі дані
    cout << *country[0] << endl;          // виводимо інформацію про місто за індексом
    country.sortByPopulation();           // здійснюємо сортування
    cout << country << endl;              // виводимо всі дані
    // Видалення міст, на які вказують вказівники в масиві cities
    for (int i = 0; i < realCount; i++)
    {
        delete cities[i];
    }
    return 0;
}