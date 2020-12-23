#include "list.h"

std::ostream & operator << (std::ostream & o, List & S)
{
	for (auto p = &S; p; p = p->next)
        o << p->e;
	return o;
}

List List::mem[List::maxmup];  //"Свободная память"
int List::mup = 0, List::mup0 = 0; //Рабочий и резервный указатели на свободное место

Set::Set() : name('A' + count++), pow(0), S(nullptr)
{
    // std::cout << "-> Создано " << name << " = {" << *S << "}, |" << name << "| = " << pow << std::endl;
}

Set::Set(char n) : name(n), pow(0), S(nullptr)
{
    count++;
    auto w = rand();

	for (int i = 0; i < U; i++)
		if ((w >> i) & 1)
            S = new List(i + 'A', S), ++pow;
	// std::cout << "-> Создано " << name << " = {" << *S << "}, |" << name << "| = " << pow << std::endl;
}

Set::Set(const Set & other) : name('A'+count++),  pow(other.pow), S(nullptr)
{
	for(auto p = other.S; p; p = p->next)
        S = new List(p->e, S);

	// std::cout << "-> Создано " << name << " = {" << *S << "}, |" << name << "| = " << pow
    // << " из " << other.name << std::endl;
}

Set & Set::operator &= (const Set& B)
{
	Set C;
	for (auto i = S; i; i = i->next)
	{
		for (auto j = B.S; j; j = j->next)
			if (i->e == j->e)
				C.S = new List(i->e, C.S), ++C.pow;
	}
	swap(C);
	// std::cout << "; Получено " << name << " = " << C.name << " & " << B.name
        // << " = {" << *S << "}, |" << name << "| = " << pow << std::endl;
	return *this;
}
Set Set::operator & (const Set& B) const
{
	Set C(*this);
	// std::cout << "Вычисление " << C.name << " & " << B.name << std::endl;
	return C &= B;
}

Set & Set::operator |= (const Set & B)
{
	Set C(*this);

	for (auto i = B.S; i; i = i->next)
	{
		bool f = true;
		for (auto j = S; f && j; j = j->next)
			f = f && (i->e != j->e);
		if (f)
			C.S = new List(i->e, C.S), ++C.pow;
	}
	swap(C);
    // std::cout << "; Получено " << name << " = " << C.name << " | " << B.name
        // << " = {" << *S << "}, |" << name << "| = " << pow << std::endl;
	return *this;
}

Set Set::operator | (const Set& B) const
{
	Set C(*this);
	// std::cout << "Вычисление " << C.name << " | " << B.name << std::endl;
	return C |= B;
}

Set Set::operator / (const Set& B) const
{
	Set C(*this);
	// std::cout << "Вычисление " << C.name << " / " << B.name << std::endl;
	return C & ~B;
}

Set Set::operator ~ () const
{
	Set C;

	for (char c = 'A'; c <= 'Z'; ++c)
	{
		bool f = true;

		for (auto j = S; j && f; j = j->next)
			if(c == j->e)
                f = false;

		if(f)
			C.S = new List(c, C.S) , ++C.pow;
	}

    // std::cout << "; Получено " << C.name << " = ~" << name
      // << " = {" << *C.S << "}, |" << C.name << "| = " << C.pow << std::endl;

	return C;
}

Set& Set::operator = (const Set & B)
{
	if (this != &B)
	{
        // std::cout << "\nУдалено " << name << " = {" << *S << "}, |" << name << "| = " << pow << std::endl;
		delete S;
		S = nullptr;
		pow = 0;
		for(List * p = B.S; p; p = p->next)
			S = new List(p->e, S), ++pow;
	}
    // std::cout << "-> Создано " << name << " = {" << *S << "}, |" << name << "| = " << pow
    // << " из " << name << std::endl;
	return *this;
}

void Set::print()
{
	std::cout << name << " = {" << *S << "}, |" << name << "| = " << pow << std::endl;
}
