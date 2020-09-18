/*

    Яловега Никита 9308
    Вариант 26

    Задача:
    U = Прописные латинские буквы
    E = A/(B&C&D)

*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

// ----- Константы -----

const int U = 26; // мощность универсума
const int ROLLS = 2; // количество повторений теста

// ----- Структуры -----

struct List
// Структура односвязного линейного списка
{
    char element;
    List* next;
    List(char e, List* n = nullptr): element(e), next(n){}
    ~List(){delete next;}
};


// ----- Прототипы функций -----

// функции конвертирования
char* to_array(List*);
char* to_array(unsigned int);
char* to_array(bool*);

unsigned int to_word(char*);
List* to_list(unsigned int);
bool* to_bool(unsigned int);

// функции реализации
char* char_array_method(clock_t*, char*, char*, char*, char*);
List* list_method(clock_t*, List*, List*, List*, List*);
bool* bool_method(clock_t*, bool*, bool*, bool*, bool*);
unsigned int word_method(clock_t*, unsigned int, unsigned int, unsigned int, unsigned int);

// декоративные фунции
void print_table(double, double, double, double);


int main()
{

    short menu;
    clock_t clock;
    double time1, time2, time3, time4;

    char* A = nullptr;
    char* B = nullptr;
    char* C = nullptr;
    char* D = nullptr;
    char* R = nullptr;

    List* lA = nullptr;
    List* lB = nullptr;
    List* lC = nullptr;
    List* lD = nullptr;
    List* lR = nullptr;

    bool* bA = nullptr;
    bool* bB = nullptr;
    bool* bC = nullptr;
    bool* bD = nullptr;
    bool* bR = nullptr;

    unsigned int wA, wB, wC, wD, wR;

    cout << "0) Подготовленный тест \n1) Ввод данных \n2) Генерация данных \n" << ">" << endl;
    cin >> menu;

    switch (menu)
    {
        // case 1: // ввод данных
        //     // Считываем строки, т.к самый удобный способ
        //
        //     // // конверитируем в машинные слова
        //     // wA = to_word(A);
        //     // wB = to_word(B);
        //     // wC = to_word(C);
        //     // wD = to_word(D);
        //
        // break;

        case 2: // генерация данных
            // Генерируем машинные слова, т.к это проще всего
            srand(time(nullptr));
            wA = rand();
            wB = rand();
            wC = rand();
            wD = rand();
        break;

        default: // Подготовленный тест
            /*
                A = {'A', 'B', 'C', 'D', 'F', 'G', 'H', 'I', 'J', '\0'};
                B = {'G', 'H', 'I', 'J', '\0'};
                C = {'A', 'B', 'H', 'I', 'J', '\0'};
                D = {'A', 'B', 'F', 'G', 'H', 'I', '\0'};
                ---
                R = {'A', 'B', 'C', 'D', 'F', 'G', 'J', '\0'};
            */
            wA = 1007;
            wB = 960;
            wC = 899;
            wD = 483;
    }

    // Основная функция
    A = to_array(wA);
    B = to_array(wB);
    C = to_array(wC);
    D = to_array(wD);
    cout << "Данные: \n";
    cout << "A = " << A << endl;
    cout << "B = " << B << endl;
    cout << "C = " << C << endl;
    cout << "D = " << D << endl;

    // Список

    lA =  to_list(wA);
    lB =  to_list(wB);
    lC =  to_list(wC);
    lD =  to_list(wD);

    lR = list_method(&clock, lA, lB, lC, lD);
    time2 = 1000*((((double)clock)/CLOCKS_PER_SEC)/ROLLS);

    delete lA;
    delete lB;
    delete lC;
    delete lD;

    // Битовая цепочка
    bA = to_bool(wA);
    bB = to_bool(wB);
    bC = to_bool(wC);
    bD = to_bool(wD);

    bR = bool_method(&clock, bA, bB, bC, bD);
    time3 = 1000*((((double)clock)/CLOCKS_PER_SEC)/ROLLS);

    delete bA;
    delete bB;
    delete bC;
    delete bD;

    // Машинное слово
    wR = word_method(&clock, wA, wB, wC, wD);
    time4 = 1000*((((double)clock)/CLOCKS_PER_SEC)/ROLLS);

    // Массив символов
    R = char_array_method(&clock, A, B, C, D);
    time1 = 1000*((((double)clock)/CLOCKS_PER_SEC)/ROLLS);

    delete A;
    delete B;
    delete C;
    delete D;

    cout << "\nРезультат: \n";
    cout << "Результат при использовании массива символов: " << R << endl;
    delete R;
    R = to_array(lR);
    cout << "Результат при использовании списка: " << R << endl;
    delete R;
    R = to_array(bR);
    cout << "Результат при использовании массива битов: " << R << endl;
    delete R;
    R = to_array(wR);
    cout << "Результат при использовании машинного слова: " << R << endl;

    delete R;
    delete bR;
    delete lR;

    print_table(time1, time2, time3, time4);

    return 0;
}



char* char_array_method(clock_t* time, char* A, char* B, char* C, char* D)
/*
    Реализация задания при помощи структуры массива символов.
    Сложность алгоритма O(n^2)
*/
{

    char* E = new char[U+1];
    char* R = new char[U+1];
    int rolls = ROLLS;
    clock_t start, stop;
    int i, j, k, r, f;

    start = clock();

    for(;rolls > 0; rolls--)
    {
        // вычисление E = (B&C&D). Сложность - O(n^2)


        for (i = 0, k = 0; B[i]; ++i)
            for(j = 0; C[j]; ++j)
                if (B[i] == C[j])
                    for (r = 0; D[r]; ++r)
                        if (B[i] == D[r])
                            E[k++] = B[i];

        E[k] = '\0';

        // Вычисление R = A / E. Сложность - O(n^2)
        for (i = 0, k = 0; A[i]; ++i)
        {
            for (j = 0, f = 1; E[j] && f; ++j)
                if (A[i] == E[j])
                    f = 0;
            if (f == 1)
                R[k++] = A[i];
        }
        R[k] = '\0';
    }


    stop = clock();

    delete E;

    *time = stop-start;
    return R;
}

List* list_method(clock_t* time, List* A, List* B, List* C, List* D)
/*
    Реализация задания при помощи структуры линейного односвязного списка.
    Сложность алгоритма O(n^2)
*/
{
    List* E = nullptr;
    List* R = nullptr;
    int rolls = ROLLS;
    clock_t start, stop;
    int f;

    start = clock();

    for(;rolls > 0; rolls--)
    {
        // вычисление E = (B&C&D). Сложность - O(n^2)

        delete E;
        E = nullptr;
        for (auto x = B; x; x = x->next)
            for(auto y = C; y; y = y->next)
                if (x->element == y->element)
                    for (auto z = D; z; z = z->next)
                        if (x->element == z->element)
                            E = new List(x->element, E);


        // Вычисление R = A / E. Сложность - O(n^2)
        delete R;
        R = nullptr;
        for (auto x = A; x; x = x->next)
        {
            f = 1;
            for (auto y = E; y && f; y = y->next)
                if (x->element == y->element)
                    f = 0;
            if (f == 1)
                R = new List(x->element, R);
        }
    }

    stop = clock();

    delete E;

    *time = stop-start;
    return R;
}

bool* bool_method(clock_t* time, bool* A, bool* B, bool* C, bool* D)
/*
    Реализация задания при помощи битовой цепочки.
    Сложность алгоритма O(1)
*/
{
    bool* result;
    int rolls = ROLLS;
    clock_t start, stop;
    result = new bool[U];

    start = clock();

    for(;rolls > 0; rolls--)

    // Сложность O(1)
        for(int i = 0; i < U; ++i)
            result[i] = A[i] && !(B[i] && C[i] && D[i]);

    stop = clock();

    *time = stop-start;
    return result;
}


unsigned int word_method(clock_t* time, unsigned int A, unsigned int B, unsigned int C, unsigned int D)
/*
    Реализация задания при помощи битовой цепочки.
    Сложность алгоритма O(1)
*/
{
    unsigned int result;
    int rolls = ROLLS;
    clock_t start, stop;

    start = clock();

    for(;rolls > 0; rolls--)

    // Сложность O(1)
        result = A & (~(B & C & D));

    stop = clock();

    *time = stop-start;
    return result;
}



char* to_array(unsigned int num)
{
    char* result = new char[U+1];
    int i,j;

    for(i = 0, j = 0; i < U; ++i)
        if(1 << i & num)
            result[j++] = i + 'A';

    result[j] = '\0';
    return result;
}

char* to_array(List* set)
{
    char* result = new char[U+1];
    int i,j;

    for(j = 0; set; set = set->next)
        result[j++] = set->element;

    result[j] = '\0';
    return result;
}

char* to_array(bool* array)
{
    char* result = new char[U+1];
    int i,j;

    for(i = 0, j = 0; i < U; ++i)
        if(array[i])
            result[j++] = i + 'A';

    result[j] = '\0';
    return result;
}

List* to_list(unsigned int num)
{
    List *head = nullptr;

    head = nullptr;
    for (int i = 0; i < U; ++i)
        if(1 << i & num)
            head = new List(i + 'A', head);

    return head;
}

unsigned int to_word(char *array)
{

    unsigned int result = 0;
    char c;

    for(int i = 0; array[i]; ++i)
        result |= 1 << (array[i] - 'A');

    return result;
}


bool* to_bool(unsigned int num)
{
    bool* result = new bool[U];
    int i = 0;
    for(i = 0; i < U; ++i)
        if(1 << i & num)
            result[i] = true;
        else
            result[i] = false;
    return result;
}



void print_table(double time1, double time2, double time3, double time4)
/*
    Вывод таблицы на экран
*/
{
    cout << "\n\nCравнение методов реализации \nКоличество повторов теста: " << ROLLS << "\n\n";

    cout << "Массив символов (сложность алгоритма - O(n^2)): " << time1 << endl;
    cout << "Список символов (сложность алгоритма - O(n^2)): " << time2 << endl;
    cout << "Битовый массив (сложность алгоритма - O(1)): " << time3 << endl;
    cout << "Машинное слово (сложность алгоритма - O(1)): " << time4 << endl;
}
