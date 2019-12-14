//define and using a reference
#include <iostream>

using namespace std;
void swapr(int & a, int & b);
void swapp(int * p,int * q);
void swapv(int a , int b);

int main(){
    int a = 23;
    int b = 34;

    cout << "a = " << a << ", b = " << b << endl;

    swapr(a, b); //别名
    cout << "swap using reference:\n"
        << "a = " << a << ", b = " << b << endl;

    swapp(&a ,&b);
    cout << "swap using pointer:\n"
        << "a = " << a << ", b = " << b << endl;


    swapv(a,b);
    cout << "swap direct :\n"
        << "a = " << a << ", b = " << b << endl;
    
    return 0;
}

void swapr(int & a, int & b){
    int temp;
    temp = a;
    a = b;
    b = temp;

}
void swapp(int * p,int * q){
    int temp;
    temp = *p;
    *p = *q;
    *q = temp;
}

void swapv(int a , int b){
    int temp;
    temp = a;
    a = b;
    b = temp;
}

