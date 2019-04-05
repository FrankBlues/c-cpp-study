//overload function template
#include <iostream>

using namespace std;
//function template prototype
template <class Any> // or typename Any
void Swap(Any &a, Any &b);

template <class Any> // new template
void Swap(Any *a,Any *b,int n);

void Show(int a[]);
const int Lim = 8;
int main()
{
    int i = 10;
    int j = 20;
    cout << "i,j = " << i << "," << j << endl;
    cout << "Using compiler-generated int swapper:\n";
    Swap(i, j); // generates void Swap(int &,int &)
    cout << "Now i,j = " << i << "," << j << endl;

    int d1[Lim] = {0,7,0,4,1,3,6,3};
    int d2[Lim] = {0,6,2,3,1,9,5,3};
    cout << "Original array: \n";
    Show(d1);
    Show(d2);
    Swap(d1,d2,Lim);
    cout << "Swapped arrays: \n";
    Show(d1);
    Show(d2);

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

template <class Any> // new template
void Swap(Any a[],Any b[],int n)
{
    Any temp;
    for (int i = 0 ; i < n ; i++)
    {
        temp = a[i];
        a[i] = b[i];
        b[i] = temp;
    }
}

void Show(int a[])
{
    cout << a[0] << a[1] << "/";
    cout << a[2] << a[3] << "/";
    for (int i = 4; i < Lim; i++)
        cout << a[i];
    cout << endl;
}