//example of a three-file program
#include <iostream>

using namespace std;
//external variable
double warming = 0.3;

//function prototype
void update(double dt);
void local();

int main()
{
    cout << "Global warming is " << warming << " degrees.\n";
    update(0.1);
    cout << "Global warming is " << warming << " degrees.\n";
    local();
    cout << "Global warming is " << warming << " degrees.\n";

    return 0;
}

void update(double dt) //modify global variable
{
    extern double warming; // optianal redeclaration //使用extern 关键词引用可以修改外部变量
    warming += dt;
    cout << "Updating global warming to " << warming;
    cout << " degrees.\n";
}

void local() //use local variable
{
    double warming = 0.8;
    cout << "Local warming = " << warming << " degrees.\n";
    cout << "But global warming = " << ::warming; //：：全局
    cout << " degrees.\n";
}