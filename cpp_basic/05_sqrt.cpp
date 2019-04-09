#include <iostream>

#include <cmath> // or <math.h>

int main()
{
    using namespace std;
    double in;
    cout << "enter a number" << endl;
    cin >> in;
    double q = sqrt(in);
    cout << "square root of input value is " << q
         << "." << endl;
    return 0;
}
