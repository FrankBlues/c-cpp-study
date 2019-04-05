// String1 class methods
#include <iostream>
#include <cstring>
#include "String1.h"
using std::cin;
using std::cout;

//initializing staitc
//不能在类声明中初始化变量，声明不分配内存
//但是枚举和const修饰的静态数据成员可以在声明中初始化
int String1::num_strings = 0;

//static method
int String1::HowMany()
{
    return num_strings;
}

int String1::length()
{
    return len;
}

//class methods
String1::String1(const char *s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings++;
}

String1::String1()
{
    len = 4;
    str = new char[1];
    str[0] = '\0';
    num_strings++;
}

String1::String1(const String1 &st)
{
    num_strings++;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
}

String1::~String1()
{
    --num_strings;
    delete[] str;
}

//overloaded poerator methods
String1 &String1::operator=(const String1 &st)
{
    if (this == &st)
        return *this;
    delete[] str;
    len = st.len;
    str = new char[len + 1];
    std::strcpy(str, st.str);
    return *this;
}
String1 &String1::operator=(const char *s)
{
    delete[] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}
//read-write char access for non-const String1
char &String1::operator[](int i)
{
    return str[i];
}
//read-only char access for const string
const char &String1::operator[](int i) const
{
    return str[i];
}

//friend
bool operator<(const String1 &st1, const String1 &st2)
{
    return (std::strcmp(st1.str, st2.str) < 0);
}
bool operator>(const String1 &st1, const String1 &st2)
{
    return st2.str < st1.str;
}
bool operator==(const String1 &st1, const String1 &st2)
{
    return (std::strcmp(st1.str, st2.str) == 0);
}

std::ostream &operator<<(std::ostream &os, const String1 &st)
{
    os << st.str;
    return os;
}
//quick and dirty String1 input
std::istream &operator>>(std::istream &is, String1 &st)
{
    char temp[String1::CINLIM];
    is.get(temp, String1::CINLIM);
    if (is)
        st = temp;
    while (is && is.get() != '\n')
        continue;
    return is;
}