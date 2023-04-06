#include <iostream>
#include <cmath>

struct Point
{
    int x;
    int y;
    int z;
};

double sqr(double x)
{
    return x * x;
}

double distance(Point p1, Point p2)
{
    return std::sqrt(((p1.x - p2.x) + (p1.y - p2.y) + (p1.z - p2.z)));
}

int main()
{
    Point p1 = {10, 10, 10};
    Point p2 = {2, 2, 2};

    std::cout << "\033[1m Result is \033[0m: ";
    std::cout << distance(p1, p2) << std::endl;
    return 0;
}