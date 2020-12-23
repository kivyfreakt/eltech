#include "char_array.h"
#include <iostream>


// конструторы

Set::Set(): name('A' + count++), pow(0), S(new char[U+1])
{
    S[0] = '\0';
}

Set::Set(char tag): name(tag), pow(0), S(new char[U+1])
{
    count++;
    auto w = rand();
    
    for (int i = 0; i < U; ++i)
        if((w >> i) & 1)
            S[pow++] = i + 'A';

    S[pow] = '\0';
}

Set::Set(const Set& other): name('A' + count++), pow(other.pow), S(new char[U+1])
{
    for (int i = 0; other.S[i]; ++i)
        S[i] = other.S[i];
    S[pow] = '\0';
}


// операции

Set & Set::operator = (const Set& other)
{
    if (this != &other)
    {
        pow = other.pow;
        for(int i = 0; other.S[i]; i++)
        {
            S[i] = other.S[i];
        }
        S[pow] = '\0';
    }
    return *this;
}

Set & Set::operator &= (const Set& other)
{
    Set C(*this);
    pow = 0;
    for (int i = 0; i < C.pow; ++i)
        for(int j = 0; j < other.pow; j++)
            if(C.S[i] == other.S[j])
                S[pow++] = C.S[i];
    S[pow] = '\0';
    return *this;
}

Set Set::operator & (const Set& other) const
{
    Set C(*this);
    return (C &= other);
}

Set & Set::operator |= (const Set& other)
{
    for (int i = 0; i < other.pow; ++i)
    {
        bool f = true;
        for(int j = 0; j < pow; j++)
            if(other.S[i] == S[j])
                f = false;
        if (f)
            S[pow++] = other.S[i];
    }
    S[pow] = '\0';
    return *this;
}

Set Set::operator | (const Set& other) const
{
    Set C(*this);
    return (C |= other);
}

Set Set::operator / (const Set& other) const
{
    Set C(*this);
    return C & (~other);
}

Set Set::operator ~ () const
{
    Set result;
    for (char c = 'A'; c <= 'Z'; ++c)
    {
        bool f = true;
        for (int j = 0; j < pow; ++j)
            if (c == S[j])
            {
                f = false;
                break;
            }
        if (f)
            result.S[result.pow++] = c;
    }
    result.S[result.pow] = 0;
    return result;
}

// интерфейс

void Set::print()
{
    std::cout << this->get_name() << " = {" << S << "}, |" << this->get_name() << "| = " << this->power() << std::endl;
}
