#include "word.h"
#include <iostream>


// конструторы

Set::Set(char tag): name(tag), S(rand()%0x3ffffff)
{
    count++;
}

// операции

Set & Set::operator = (const Set& other)
{
    if (this != &other)
        S = other.S;
    return *this;
}

Set Set::operator & (const Set& other) const
{
    Set C;
    C.S = S & other.S;
    return C;
}


Set Set::operator | (const Set& other) const
{
    Set C;
    C.S = S | other.S;
    return C;
}

Set Set::operator / (const Set& other) const
{
    Set C;
    C.S = S & ~other.S;
    return C;
}

Set Set::operator ~ () const
{
    Set C;
    C.S = ~S & 0x3ffffff;
    return C;
}

// интерфейс

int Set::power()
{
    int pow = 0;
    unsigned int n = S;
    while(n != 0)
    {
        pow++;
        n &= (n-1);
    }
    return pow;
}


void Set::print()
{
    char* result = new char[U+1];
    int i,j;

    for(i = 0, j = 0; i < U; ++i)
        if(1 << i & S)
            result[j++] = i + 'A';

    result[j] = '\0';

    std::cout << name << " = {" << result << "}, |" << name << "| = " << this->power() << std::endl;

    delete [] result;
}
