#include <iostream>
using namespace std;

class Building
{
public:
    Building(int num, int floors) : number(num), numFloors(floors) {}
    virtual void getInfo()
    {
        cout << "Building number " << number << " has " << numFloors << " floors." << endl;
    }

protected:
    int number;
    int numFloors;
};

class EducationalBuilding : public Building
{
public:
    EducationalBuilding(int num, int floors, int classrooms) : Building(num, floors), numClassrooms(classrooms) {}
    void getInfo()
    {
        cout << "Educational building number " << number << " has " << numFloors << " floors and " << numClassrooms << " classrooms." << endl;
    }

private:
    int numClassrooms;
};

int main()
{
    Building b1(101, 3);
    Building b2(102, 4);
    EducationalBuilding e1(201, 5, 20);
    EducationalBuilding e2(202, 6, 25);

    Building *buildings[4] = {&b1, &b2, &e1, &e2};
    for (int i = 0; i < 4; i++)
    {
        buildings[i]->getInfo();
    }

    return 0;
}
