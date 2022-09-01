
#include <iostream>
#include <string>

using namespace std;



class Numbered
{
public:
    Numbered(){mysn = unique++;}
    Numbered(const Numbered &sn){mysn = unique++;}
    int mysn;
    static int unique;
};

int Numbered::unique = 10;

void f(const Numbered &n)
{
    cout << n.mysn << endl;
}

void exercise1317()
{
    Numbered a, b = a, c = b;
    f(a); f(b); f(c);
}


int main(int argc, char const *argv[])
{
    exercise1317();
    return 0;
}
