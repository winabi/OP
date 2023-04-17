#include <iostream>
#include <cmath>

// Клас для представлення точки на екрані
class Point3D
{
    friend double operator-(const Point3D &p1, const Point3D &p2)
    {
        double dx = p1.x - p2.x;
        double dy = p1.y - p2.y;
        double dz = p1.z - p2.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }

private:
    double x, y, z; // координати точки
public:
    // Конструктор без параметрів викликає інший конструктор:
    Point3D() : Point3D(0, 0, 0) {}

    // Конструктор ініціалізує елементи даних:
    Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

    double getX() const { return x; }
    void setX(double x) { this->x = x; }
    double getY() const { return y; }
    void setY(double y) { this->y = y; }
    double getZ() const { return z; }
    void setZ(double z) { this->z = z; }

    // Допоміжна статична функція обчислення другого степеня:
    static double sqr(double x) { return x * x; }
};

int main()
{
    // Першу точку створюємо за допомогою конструктора з параметрами:
    Point3D p1;
    Point3D p2(1, 2, 3);
    std::cout << p1.getX() << " " << p1.getY() << " " << p1.getZ() << "\n";
    std::cout << p2.getX() << " " << p2.getY() << " " << p2.getZ() << "\n";

    double distance = p2 - p1;
    std::cout << "Distance between p1 and p2: " << distance << std::endl;

    // Для другої точки координати вказуємо сеттерами:
    p2.setX(4);
    p2.setY(6);
    p2.setZ(7);
    std::cout << p2.getX() << " " << p2.getY() << " " << p2.getZ() << "\n";

    // Обчислюємо відстань:
    std::cout << "Distance between p1 and p2: " << operator-(p1, p2) << std::endl;

    return 0;
}