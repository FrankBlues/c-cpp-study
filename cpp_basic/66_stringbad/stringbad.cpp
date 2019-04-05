// stringbad class methods
#include <iostream>
#include "stringbad.h"
using std::cout;

//initializing staitc
//不能在类声明中初始化变量，声明不分配内存
//但是枚举和const修饰的静态数据成员可以在声明中初始化
int Stringbad::num_strings = 0;

Stringbad::Stringbad(const char *s)
{
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings++;
    cout << num_strings << ": \"" << str
         << str << "\" object created \n";
}

Stringbad::Stringbad()
{
    len = 4;
    str = new char[4];
    std::strcpy(str, "C++");
    num_strings++;
    cout << num_strings << ": \"" << str
         << str << "\" object created \n";
}
Stringbad::~Stringbad()
{
    cout << "\"" << str << "\" object deleted \n";
    --num_strings;
    cout << num_strings << " left \n";
    delete[] str;
}
//friend
std::ostream &operator<<(std::ostream &os, const Stringbad &st)
{
    os << st.str;
    return os;
}