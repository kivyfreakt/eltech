/*
    Яловега Никита 9308
*/

#ifndef CHAR_H
#define CHAR_H

class Set
{
    private:
        static int U, count; // мощность юниверсума и количество множеств
        char name; // название множества
        int pow; // мощность множества
        char *S; // память для множества
    public:
        Set(char); // конструктор класса
        Set(); // конструктор по умолчанию
        Set(const Set&); // конструтор копирования
        ~Set(){delete [] S;} // деструктор класса

        // операции над множествами
        Set& operator= (const Set&);
        Set& operator &= (const Set&);
        Set operator & (const Set&) const;
        Set& operator |= (const Set&);
        Set operator | (const Set&) const;
        Set operator / (const Set&) const;
        Set operator ~ () const;

        // интерфейс
        inline char get_name() {return name;}
        inline int power() {return pow;}

        void print();
    };

#endif
