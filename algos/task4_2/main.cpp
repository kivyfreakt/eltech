#include <iostream>
#include <cstdlib>
#include <ctime>

#include "tree.h"

using namespace std;

int main()
{
    srand(time(nullptr));
    int n;
    cin >> n;
    Tree t1;
    Tree t2('0');

    if (t1.is_isomorph(t2))
        cout << "Деревья изоморфны\n";
    else
        cout << "Деревья не изоморфны\n";
    return 0;
}
