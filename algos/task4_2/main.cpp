#include <iostream>
#include <cstdlib>
#include <ctime>

#include "tree.h"

using namespace std;

const int MAXV = 26;

void example();
void input();
void generate();
short get_num_nodes();

int main()
{
    srand(time(nullptr));
    int menu;

    do
    {
        cout << "1 - Использовать пример\n";
        cout << "2 - Ввести деревья\n";
        cout << "3 - Сгенерировать деревья\n";
        cout << "0 - Выход\n";
        cout << "Введите пункт: ";

        cin >> menu;
        switch(menu)
        {
            case 1:
                example();
                break;
            case 2:
                input();
                break;
            case 3:
                generate();
                break;
            case 0:
                cout << "До свидания!\n";
                break;
            default:
                cout << "Такого пункта не существует!\n";
        }
    }
    while(menu);
    return 0;
}


void example()
{
    Tree t1;
    Tree t2('0');

    if (t1.is_isomorph(&t2))
        cout << "\nДеревья изоморфны\n\n\n";
    else
        cout << "\nДеревья не изоморфны\n\n\n";
}

void input()
{
    int n = get_num_nodes();
    Tree t1(n), t2(n);

    if (t1.is_isomorph(&t2))
        cout << "\nДеревья изоморфны\n\n\n";
    else
        cout << "\nДеревья не изоморфны\n\n\n";
}


void generate()
{
    int n = get_num_nodes();
    Tree t1(n, '0'), t2(n, '0');

    if (t1.is_isomorph(&t2))
        cout << "\nДеревья изоморфны\n\n\n";
    else
        cout << "\nДеревья не изоморфны\n\n\n";
}


short get_num_nodes()
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
