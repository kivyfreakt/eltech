#include <iostream>
#include <ctime>

using namespace std;

// #include "char_array.h"
#include "list.h"
// #include "bool.h"
// #include "word.h"

int Set::U = 26;
int Set::count = 0;

// const long ROLLS = 10000000;
const long ROLLS = 3;

int main()
{
    List::clear();
    srand(time(NULL));
    Set A('A'), B('B'), C('C'), D('D'), E;
    List::mark();
    clock_t start = clock();

    for (long rolls = 0; rolls < ROLLS; rolls++)
    {
        List::release();
        E = A/(B&C&D);
    }

    clock_t end = clock();

    cout << "Множества: \n";
    A.print();
    B.print();
    C.print();
    D.print();
    cout << "Результат: \n";
    E.print();
    cout << "--- \n";
    cout << "Среднее время: " << 1000*((((double)(end - start))/CLOCKS_PER_SEC)/ROLLS) <<
        " мс. Количество повторений: " << ROLLS << endl;

    return 0;
}
