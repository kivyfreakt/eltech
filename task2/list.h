/*
    Яловега Никита 9308
*/

#ifndef LIST_H
#define LIST_H

class List{
	char e;
	List *next; // указатель на следующий элемент списка
	static const int maxmup = 200; // максимальное количество элементов
	static List mem[maxmup]; // память для элементов списков
	static int mup, mup0;
public:
	List(): e('+'), next(nullptr){} // конструктор по умолчанию
	List(char e, El *n = nullptr): e(e), next(n) { std::cout << "+" << e; }
	~List(){ if(this) {//Прямой вызов деструктора требует такой проверки!!!
                delete next;
		std::cout << "-" << e;
		e = '-'; }
	else cout << "<Empty!>";
	}
	static void* operator new(size_t) { //Перегрузка new и delete - только функциями static!!!
           return (mup < maxmup? &mem[mup++] : nullptr); }
	static void operator delete(void *, size_t) { }
	static void mark(){ mup0 = mup;}	//Фиксировать состояние памяти
	static void release() { mup = mup0; }   //Сбросить до фиксированного
	static void clear(){ mup = 0; }	        //Очистить память полностью
	friend class Set;
	friend std::ostream & operator << ( std::ostream & o, El & S); //Перегрузка << для вывода
	friend static void memOut();  //Вспомогательная функция для вывода содержимого памяти
};

std::ostream & operator << (std::ostream & o, El & S)
{
	for (auto p = &S; p; p = p->next)
        o << p->e;
	return o;
}

El El::mem[El::maxmup];  //"Свободная память"
int El::mup = 0, El::mup0 = 0; //Рабочий и резервный указатели на свободное место

void memOut() //Вывод использованного содержимого "свободной памяти"
{
	std::cout << "\n\nMemory for list elements (total - " << std::dec << El::mup << ")\n";
	for(int i = 0; i < El::maxmup; ++i) cout << El::mem[i].e;
}

class Set
{
    private:
        static int U, count; // мощность юниверсума и количество множеств
        char name; // название множества
        int pow; // мощность множества
        List* S; // память для множества
    public:
        Set(): name('A' + count++), S(0){} // конструктор по умолчанию
        Set(char); // конструктор класса
        Set(const Set& other): name('A' + count++), S(other.S){} // конструтор копирования

        // операции над множествами
        Set& operator = (const Set&);
        Set & operator |= (const Set&);
        Set & operator &= (const Set&);
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
