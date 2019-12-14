//function template
#include <iostream>

using namespace std;
//function template prototype
template <class Any> // or typename Any
void Swap(Any &a, Any &b);

int main()
{
    int i = 10;
    int j = 20;
    cout << "i,j = " << i << "," << j << endl;
    cout << "Using compiler-generated int swapper:\n";
    Swap(i, j); // generates void Swap(int &,int &)
    cout << "Now i,j = " << i << "," << j << endl;

    double x = 24.5;
    double y = 81.7;
    cout << "x,y = " << x << "," << y << endl;
    cout << "Using compiler-generated double swapper:\n";
    Swap(x, y); // generates void Swap(double &,double &)
    cout << "Now x,y = " << x << "," << y << endl;

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