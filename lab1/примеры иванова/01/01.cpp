#include <iostream>

enum DayOfWeek {
    Sunday, 
    Monday, 
    Tuesday, 
    Wednesday,
    Thursday, 
    Friday, 
    Saturday
};

// Перевантаження префіксної операції ++
DayOfWeek operator++(DayOfWeek& day)
{
    if (day == Saturday) // окремий випадок
    {
        day = Sunday;
    }
    else
    {
        day = (DayOfWeek) (day + 1); // всі інші дні
    }
    return day;
}

// Перевантаження постфіксної операції ++
DayOfWeek operator++(DayOfWeek& day, int)
{
    DayOfWeek oldDay = day;// зберігаємо попередній день
    operator++(day);       // викликаємо попередню функцію
    return oldDay;         // повертаємо попередній день
}

// Отримання назв днів тижня
const char* getName(DayOfWeek day)
{
    switch (day)
    {
        case Sunday: 
            return "Sunday";
        case Monday:
            return "Monday";
        case Tuesday:
            return "Tuesday";
        case Wednesday:
            return "Wednesday";
        case Thursday:
            return "Thursday";
        case Friday:
            return "Friday";
        default:
            return "Saturday";
    }
}

int main()
{
    // Послідовно виводимо дні від середи до наступного понеділка
    for (DayOfWeek d = Wednesday; d != Tuesday; d++)
    {
        std::cout << getName(d) << "\n";
    }
    return 0;
}