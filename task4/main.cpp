#include <iostream>
#include <cstdlib>
#include <ctime>

#include "graph.h"

using namespace std;

const int MAXV = 26; // максимальное количество вершин

short get_num_nodes();
void input_case();
void generate_case();
void example_case();

int main()
{
    srand(time(nullptr));
    int menu_item;

    do
    {
        cout << "1 - Ввести граф\n";
        cout << "2 - Сгенерировать граф\n";
        cout << "3 - Использовать пример\n";
        cout << "0 - Выход\n";
        cout << "> ";
        
        cin >> menu_item;
        switch(menu_item)
        {
            case 1:
                input_case();
                break;
            case 2:
                generate_case();
                break;
            case 3:
                example_case();
                break;
            case 0:
                cout << "";
                break;
            default:
                cout << "Такого пункта не существует, повторите ввод!\n";
        }
    }
    while(menu_item);

    return 0;
}

void input_case()
{
    int n = get_num_nodes();
    Graph g(n);
    Forest f = g.spanning_forest();
    f.print();
}

void generate_case()
{
    int n = get_num_nodes();
    Graph g(n, 0);
    Forest f = g.spanning_forest();
    f.print();
}

void example_case()
{
    Graph g;
    Forest f = g.spanning_forest();
    f.print();
}

short get_num_nodes()
/*
    Обработка ввода количества вершин
*/
{
    int n;

    do
    {
        cout << "Введите количество вершин графа (число от 1 до " << MAXV << "): ";
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
            cout << "\nЧисло вершин не должно превышать " << MAXV << '\n';
        if (n < 1)
            cout << "\nЧисло вершин не должно быть отрицательным или 0\n";
        }

    } while(cin.fail() || n < 1 || n > MAXV);

    return n;
}
