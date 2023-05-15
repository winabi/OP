#include <iostream>
#include <fstream>
#include <map>
#include <set>

using std::cout;
using std::endl;
using std::ifstream;
using std::map;
using std::set;

int main()
{
    map<int, int> m;
    set<int> list = {1, 2, 3, 4};

    int i;
    {
        ifstream in("values.txt");
        while (in >> i)
        {
            if (list.count(i) != 0) // Исправлено: проверяем наличие i в множестве list
            {
                cout << i << "  - this number from the list" << endl;
                // Исправлено: устанавливаем значение 1, так как это первое вхождение числа i
            }
            else
            {
                m[i]++; // Исправлено: увеличиваем счетчик для числа i
            }
        }
    }
    map<int, int>::iterator mi;
    for (mi = m.begin(); mi != m.end(); mi++)
    {
        cout << mi->first << " " << mi->second << endl;
    }
    return 0;
}
