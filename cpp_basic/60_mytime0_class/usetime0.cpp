//use time class
#include <iostream>
#include "mytime0.h"

int main()
{
    using std::cout;
    using std::endl;
    Time planning;
    Time coding(2, 40); //另一种初始化类方法
    Time fixing(5, 55);
    Time total;

    cout << "Planning time = ";
    planning.Show();
    cout << endl;

    cout << "Coding time = ";
    coding.Show();
    cout << endl;

    cout << "fixing time = ";
    fixing.Show();
    cout << endl;

    total = coding.sum(fixing);
    cout << "coding.sum(fixing) = ";
    total.Show();
    cout << endl;
    return 0;
}