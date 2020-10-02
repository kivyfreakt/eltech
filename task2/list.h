/*
    Яловега Никита 9308
*/

#ifndef LIST_H
#define LIST_H

struct List
// Структура односвязного линейного списка
{
    char element;
    List* next;
    List(char e, List* n = nullptr): element(e), next(n){}
    ~List(){delete next;}
};

class Set
{
    private:
        static int U, count; // мощность юниверсума и количество множеств
        char name; // название множества
        int pow; // мощность множества
        List* S; // память для множества
    public:
        Set(char); // конструктор класса
        Set(): name('A' + count++), S(0){} // конструктор по умолчанию
        Set(const Set& other): name('A' + count++), S(other.S){} // конструтор копирования
        // операции над множествами
        Set& operator= (const Set&);
        Set operator & (const Set&) const;
        Set operator | (const Set&) const;
        Set operator / (const Set&) const;
        Set operator ~ () const;

        // интерфейс
        inline char get_name() {return name;}
        int power();

        void print();
    };

#endif
