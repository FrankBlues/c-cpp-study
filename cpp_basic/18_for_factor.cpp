#include <iostream>

using namespace std;

const int ArSize = 16;

int main()
{
    double factorials[ArSize];         // store result
    factorials[0] = factorials[1] = 1; // 0!
    int i;
    for (i = 2; i < ArSize; i++)
        factorials[i] = i * factorials[i - 1];

    for (i = 0; i < ArSize; i++)
        cout << i << "! = " << factorials[i] << endl;

    return 0;
}
