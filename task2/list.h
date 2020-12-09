#ifndef LIST_H
#define LIST_H

#include <iostream>

class List{
	char e;
	List *next; // указатель на следующий элемент списка
	static const int maxmup = 200; // максимальное количество элементов
	static List mem[maxmup]; // память для элементов списков
	static int mup, mup0;
public:
	List(): e('!'), next(nullptr){} // конструктор по умолчанию
	List(char e, List *n = nullptr): e(e), next(n) { /* std::cout << "+" << e; */ }
	~List(){
        if(this)
        {//Прямой вызов деструктора требует такой проверки!!!
                delete next;
		        // std::cout << "-" << e;
                e = '-';
        }
	       else std::cout << "<Empty!>";
	}
	static void* operator new(size_t) { //Перегрузка new и delete - только функциями static!!!
           return (mup < maxmup? &mem[mup++] : nullptr); }
	static void operator delete(void *, size_t) { }
	static void mark(){ mup0 = mup;}
	static void release() { mup = mup0; }
	static void clear(){ mup = 0;}
	friend class Set;
	friend std::ostream & operator << ( std::ostream & o, List & S); //Перегрузка << для вывода
};

class Set
{
    private:
        static int U, count; // мощность юниверсума и количество множеств
        char name; // название множества
        int pow; // мощность множества
        List* S; // память для множества
    public:
        Set(); // конструктор по умолчанию
        Set(char); // конструктор класса
        Set(const Set&); // конструтор копирования
        ~Set()
        {
            std::cout << "\nУдалено " << name << " = {" << *S << "}, |" << name << "| = " << pow << std::endl;
            S->List::~List(); //Здесь нужен явный вызов деструктора
        }
        // операции над множествами
        Set& operator = (const Set&);
        Set & operator |= (const Set&);
        Set & operator &= (const Set&);
        Set operator & (const Set&) const;
        Set operator | (const Set&) const;
        Set operator / (const Set&) const;
        Set operator ~ () const;
        void swap(Set & other) {std::swap(pow, other.pow); std::swap(S, other.S);}
        // интерфейс
        char get_name() {return name;}
        int power();

        void print();
    };

#endif
