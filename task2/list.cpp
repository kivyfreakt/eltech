#include "list.h"
#include <iostream>


Set::Set() : name('A' + count++), pow(0), S(nullptr)
{
    std::cout << "-> Created " << name << "(" << pow << ") = [" << *S << "] \n";
}

Set::Set(char n) : name(n), pow(0), S(nullptr)
{
    count++;
    auto w = rand();

	for (int i = 0; i < U; i++)
		if ((w >> i) & 1)
            S = new El(i + 'A', A), ++pow;

	std::cout << "-> Created " << name << "(" << pow << ") = [" << *S << "] \n";
}

Set::Set(const Set & other) : name('A'+count++),  pow(other.pow), S(nullptr)
{
	for(auto p = other.S; p; p = p->next)
        S = new El(p->e, S);

	std::cout << "-> Created " << name << "(" << pow << ") = ["
                  << *S << "] from " << other.name << std::endl;
}

Set & Set::operator &= (const Set& B)
{
	Set C;
	for (auto i = S; i; i = i->next)
	{
		for (auto j = B.S; j; j = j->next)
			if (i->e == j->e)
				C.S = new El(i->e, C.S), ++C.pow;
	}
	swap(C);
	std::cout << "; Received " << name << "(" << pow << ") = ["
                  << *S << "] = " << C.name << "&" << B.name << std::endl;
	return *this;
}
Set Set::operator & (const Set& B) const
{
	Set C(*this);
	std::cout << "Calculation " << C.name << " & " << B.name << std::endl;
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
			C.S = new El(i->e, C.S), ++C.pow;
	}
	swap(C);
	std::cout << "; Received " << name << "(" << pow << ") = ["
                  << *S << "] = " << C.name << "|" << B.name << std::endl;
	return *this;
}

Set Set::operator | (const Set& B) const
{
	Set C(*this);
	std::cout << "Calculation " << C.name << " | " << B.name << std::endl;
	return C |= B;
}

Set Set::operator / (const Set& B) const
{
	Set C(*this);
	std::cout << "Calculation " << C.name << " / " << B.name << std::endl;
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
			C.S = new El(c, C.S) , ++C.pow;
	}

	std::cout << "; Received " << C.name << "(" << C.pow << ") = [" << *C.S
                  << "] = ~" << name << std::endl;

	return C;
}

// Set& Set::operator = (const Set & B)
// {
// 	if (this != &B)
// 	{   std::cout << "\nDeleted " << S << "(" << n << ") = [" << *A << "]";
// 		delete A;
// 		A = nullptr;
// 		n = 0;
// 		for(El * p = B.A; p; p = p->next)
// 			A = new El(p->e, A), ++n;
// 		S = 'A'+num++;
// 	}
// 	std::cout << "; Created " << S << "(" << pow << ") = [" << *A << "] from "
//                 << B.S << std::endl;
// 	return *this;
// }

void Set::print()
{
	std::cout << '\n' << name << "(" << pow << ") = [" << *A << "]";
}
