#include <iostream>

enum Seasons
{
    spring,
    summer,
    autumn,
    winter
};

Seasons operator++(Seasons &month)
{
    if (month == winter)
    {
        month = spring;
    }
    else
    {
        month = (Seasons)(month + 1);
    }
    return month;
}

Seasons operator++(Seasons &month, int)
{
    Seasons oldMonth = month;
    operator++(month);
    return month;
}

const char *getMonth(Seasons month)
{
    switch (month)
    {
    case spring:
        return "spring";
    case summer:
        return "summer";
    case autumn:
        return "autumn";
    default:
        return "winter";
    }
}

int main()
{
    // послідово вивовимо сезони від лютого до winter
    for (Seasons d = spring; d != winter; d++)
    {
        std::cout << getMonth(d) << std::endl;
    }
    std::cout << getMonth(winter) << std::endl;
    return 0;
}