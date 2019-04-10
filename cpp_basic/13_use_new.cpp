#include <iostream>

using namespace std;

int main()
{

    int *pt = new int; //运行时分配内存
    *pt = 1011;
    cout << "int value = " << *pt << endl;
    cout << "mem location : " << pt << endl;

    double *pd = new double;
    *pd = 10000001.01;

    cout << "double value pd = " << *pd << endl;
    cout << "mem location : " << pd << endl;

    cout << "size of pt = " << sizeof(pt) << endl;
    cout << "size of *pt = " << sizeof(*pt) << endl;

    cout << "size of pd = " << sizeof pd << endl;
    cout << "size of *pd = " << sizeof(*pd) << endl;

    delete pt;
    delete pd; // 与new配合使用

    return 0;
}
