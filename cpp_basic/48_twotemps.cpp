//overload function template(explicit specialization)
#include <iostream>

using namespace std;
//function template prototype
template <class Any> // or typename Any
void Swap(Any &a, Any &b);

struct job
{
    char name[40];
    double salary;
    int floor;
};

// explicit specialization 显示具体化
template <> void Swap<job>(job &j1, job &j2);

void Show(job &j);
const int Lim = 8;
int main()
{
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);
    int i = 10;
    int j = 20;
    cout << "i,j = " << i << "," << j << endl;
    cout << "Using compiler-generated int swapper:\n";
    Swap(i, j); // generates void Swap(int &,int &)
    cout << "Now i,j = " << i << "," << j << endl;

    job sue = {"Susan Yaffee", 7300.6, 7};
    job sidney = {"Sidney Taffee", 7800.5, 9};
    cout << "Befor job swapper:\n";
    Show(sue);
    Show(sidney);
    Swap(sue, sidney);
    cout << "After job swapper:\n";
    Show(sue);
    Show(sidney);

    return 0;
}

template <class Any> // or typename Any
void Swap(Any &a, Any &b)
{
    Any temp;
    temp = a;
    a = b;
    b = temp;
}

// swaps just memers of job
template <>
void Swap<job>(job &j1, job &j2)
{
    double t1;
    int t2;
    t1 = j1.salary;
    j1.salary = j2.salary;
    j2.salary = t1;

    t2 = j1.floor;
    j1.floor = j2.floor;
    j2.floor = t2;
}

void Show(job &j)
{
    cout << j.name << ": $" << j.salary
         << " on floor " << j.floor << endl;
}
