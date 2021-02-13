#include "bool.h"
#include <iostream>


// конструторы

Set::Set(): name('A' + count++), S(new bool[U])
{
    for (int i = 0; i < U; ++i)
        S[i] = 0;
}

Set::Set(char tag): name(tag), S(new bool[U])
{
    count++;
    for (int i = 0; i < U; ++i)
        S[i] = rand()%2;
}

Set::Set(const Set& other): name('A' + count++), S(new bool[U])
{
    for (int i = 0; i < U; ++i)
        S[i] = other.S[i];
}


// операции

Set & Set::operator = (const Set& other)
{
    if (this != &other)
    {
        for (int i = 0; i < U; ++i)
            S[i] = other.S[i];
    }
    return *this;
}


Set Set::operator & (const Set& other) const
{
    Set C;
    for (int i = 0; i < U; ++i)
        C.S[i] = S[i] && other.S[i];
    return C;
}


Set Set::operator | (const Set& other) const
{
    Set C;
    for (int i = 0; i < U; ++i)
        C.S[i] = S[i] || other.S[i];
    return C;
}

Set Set::operator / (const Set& other) const
{
    Set C;
    for (int i = 0; i < U; ++i)
        C.S[i] = S[i] && !other.S[i];
    return C;
}

Set Set::operator ~ () const
{
    Set C;
    for (int i = 0; i < U; ++i)
        C.S[i] = !S[i];
    return C;
}

// интерфейс

int Set::power()
{
    int counter = 0;
    for (int i = 0; i < U; ++i)
        if (S[i])
            counter++;
    return counter;
}

void Set::print()
{
    char* result = new char[U+1];
    int i,j;

    for(i = 0, j = 0; i < U; ++i)
        if(S[i])
            result[j++] = i + 'A';

    result[j] = '\0';

    std::cout << name << " = {" << result << "}, |" << name << "| = " << this->power() << std::endl;

    delete [] result;
}
