#include <iostream>
#include <cstdlib>
#include <ctime>

#include "graph.h"

using namespace std;

const int MAXV = 20; // максимальное количество вершин

short get_num_nodes();

int main()
{
    srand(time(nullptr));
    int menu_item, n;
    // do
    // {
    //     cin.sync();
    //     cout << "1 - Ввести граф\n";
    //     cout << "2 - Сгенерировать граф\n";
    //     cout << "3 - Использовать пример\n";
    //     cout << "> ";
    //     cin >> menu_item;
    //     switch(menu_item)
    //     {
    //         case 1:
    //             n = get_num_nodes();
    //             Graph g(n);
    //             cout << "\n\nВведенный граф:\n";
    //             g.spanning_forest();
    //             break;
    //         case 2:
    //             n = get_num_nodes();
    //             Graph g(n, 1);
    //             cout << "\n\nСгенерированный граф:\n";
    //             g.spanning_forest();
    //             break;
    //         default:
    //             cout << "Такого пункта не существует, повторите ввод!\n";
    //     }
    //     if(cin.fail())
    //     {
    //         cin.clear();
    //         cin.ignore(32767,'\n');
    //     }
    // }
    // while(menu_item > 2 || menu_item < 1 || cin.fail());
    n = get_num_nodes();
    Graph g(n, 1);
    Forest f = g.spanning_forest();
    f.print();
    return 0;
}

short get_num_nodes()
/*
    Обработка ввода количества вершин
*/
{
    int n;

    do
    {
        cout << "Введите количество вершин графа (число от 0 до " << MAXV << "): ";
        cin >> n;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767,'\n');
            cout << "\nНекорректный ввод. Попробуйте еще раз\n";
        }
        else
        {
        if (n > MAXV)
            cout << "\nЧисло вершин не должно превышать 20.\n";
        if (n < 1)
            cout << "\nЧисло вершин не должно быть отрицательным или 0.\n";
        }

    } while(cin.fail() || n < 1 || n > MAXV);

    return n;
}
