#include <iostream>

using namespace std;

//变量声明

extern int a, b;
extern int c;
extern float f;

int main()
{
    //定义
    int a, b;
    int c;
    float f;
    //初始化
    a = 10;
    b = 20;
    c = a + b;

    cout << c << endl;

    f = 70 / 3.0;
    cout << f << endl;

    return 0;
}
