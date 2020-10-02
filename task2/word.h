/*
    Яловега Никита 9308
*/

#ifndef WORD_H
#define WORD_H

class Set
{
    private:
        static int U, count; // мощность юниверсума и количество множеств
        char name; // название множества
        unsigned int S; // память для множества
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
