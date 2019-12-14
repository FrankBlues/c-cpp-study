// use class

#include <iostream>
#include "stringbad.h"
using std::cout;

void callme1(Stringbad &);
void callme2(Stringbad);

int main()
{
    using std::endl;
    Stringbad headline1("Celery Stalks at Midnight");
    Stringbad headline2("Lettuce Prey");
    Stringbad sports("Spinach Leaves Bowl for Dollars");
    cout << "headline1: " << headline1 << endl;
    cout << "headline2: " << headline2 << endl;
    cout << "sports: " << sports << endl;
    callme1(headline1);
    cout << "headline1: " << headline1 << endl;
    callme2(headline2); //按值传递导致析构函数被调用
    cout << "headline2: " << headline2 << endl;

    cout << "Initialize one objet to another: \n";
    Stringbad sailor = sports; // 隐式复制构造函数，自动创建 Stringbad(Stringbad &)构造函数 容易造成问题
    cout << "Sailor: " << sailor << endl;
    cout << "Assign one object to another: \n";
    Stringbad knot;
    knot = headline1; //隐式 赋值操作符
    cout << "knot: " << knot << endl;
    cout << " End of main()\n";
    return 0;
}

void callme1(Stringbad &rst)
{
    cout << " String passed by reference : \n";
    cout << "  \"" << rst << "\"\n";
}
void callme2(Stringbad st)
{
    cout << " String passed by value : \n";
    cout << "  \"" << st << "\"\n";
}
