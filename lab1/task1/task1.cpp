#include <iostream>

enum Months
{
    СІЧЕНЬ,
    ЛЮТИЙ,
    БЕРЕЗЕНЬ,
    КВІТЕНЬ,
    ТРАВЕНЬ,
    ЧЕРВЕНЬ,
    ЛИПЕНЬ,
    СЕРПЕНЬ,
    ВЕРЕСЕНЬ,
    ЖОВТЕНЬ,
    ЛИСТОПАД,
    ГРУДЕНЬ
};

Months operator++(Months &month)
{
    if (month == ГРУДЕНЬ)
    {
        month = СІЧЕНЬ;
    }
    else
    {
        month = (Months)(month + 1);
    }
    return month;
}

Months operator++(Months &month, int)
{
    Months oldMonth = month;
    operator++(month);
    return month;
}

const char *getMonth(Months month)
{
    switch (month)
    {
    case СІЧЕНЬ:
        return "СІЧЕНЬ";
    case ЛЮТИЙ:
        return "ЛЮТИЙ";
    case БЕРЕЗЕНЬ:
        return "БЕРЕЗЕНЬ";
    case КВІТЕНЬ:
        return "КВІТЕНЬ";
    case ТРАВЕНЬ:
        return "ТРАВЕНЬ";
    case ЧЕРВЕНЬ:
        return "ЧЕРВЕНЬ";
    case ЛИПЕНЬ:
        return "ЛИПЕНЬ";
    case СЕРПЕНЬ:
        return "СЕРПЕНЬ";
    case ВЕРЕСЕНЬ:
        return "ВЕРЕСЕНЬ";
    case ЖОВТЕНЬ:
        return "ЖОВТЕНЬ";
    case ЛИСТОПАД:
        return "ЛИСТОПАД";
    default:
        return "ГРУДЕНЬ";
    }
}

int main()
{
    // послідово вивовимо місяці від лютого до січня
    for (Months d = ЛЮТИЙ; d != СІЧЕНЬ; d++)
    {
        std::cout << getMonth(d) << std::endl;
    }
    std::cout << getMonth(СІЧЕНЬ) << std::endl;
    return 0;
}