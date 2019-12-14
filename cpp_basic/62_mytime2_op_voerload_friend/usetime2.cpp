//use time class
#include <iostream>
#include "mytime2.h"

int main()
{
    using std::cout;
    using std::endl;
    Time planning;
    Time coding(2, 40); //另一种初始化类方法
    Time fixing(5, 55);
    Time total;

    cout << "Planning time = ";
    cout << planning;
    cout << endl;

    cout << "Coding time = ";
    cout << coding;
    cout << endl;

    cout << "fixing time = ";
    cout << fixing;
    cout << endl;

    //total = coding.operator+(fixing);
    total = coding + fixing;
    cout << "coding + fixing (total) = ";
    cout << total;
    cout << endl;

    Time temp;
    temp = total * 1.17;
    cout << "total * 1.17 = " << temp << endl;
    cout << "10 * total: " << 10 * total << endl; 

    return 0;
}