//using placement new
#include <iostream>
#include <new>

using namespace std;
const int BUF = 512;
const int N = 5;
char buffer[BUF]; //chunk of memory

int main()
{
    double *pd1, *pd2;
    int i;
    cout << "Calling new and placement new:\n";
    pd1 = new double[N];          // use heap
    pd2 = new (buffer) double[N]; //use buffer array

    for (i = 0; i < N; i++)
        pd2[i] = pd1[i] = 1000 + 20.0 * i;
    cout << "Buffer addressed:\n"
         << " heap: " << pd1
         << " static: " << (void *)buffer << endl;
    cout << "Buffer contents:\n";

    for (i = 0; i < N; i++)
    {
        cout << pd1[i] << " at " << &pd1[i] << ";\n";
        cout << pd2[i] << " at " << &pd2[i] << ";\n";
    }

    cout << "\nCalling new and placement new a second time :\n";
    double *pd3, *pd4;
    pd3 = new double[N];          // use heap
    pd4 = new (buffer) double[N]; //use buffer array

    for (i = 0; i < N; i++)
        pd4[i] = pd3[i] = 1000 + 20.0 * i;

    cout << "Buffer contents:\n";
    for (i = 0; i < N; i++)
    {
        cout << pd3[i] << " at " << &pd3[i] << ";\n";
        cout << pd4[i] << " at " << &pd4[i] << ";\n";
    }

    cout << "\nCalling new and placement new a third time :\n";
    double *pd5, *pd6;
    pd5 = new double[N];          // use heap
    pd6 = new (buffer) double[N]; //use buffer array

    for (i = 0; i < N; i++)
        pd6[i] = pd5[i] = 1000 + 20.0 * i;

    cout << "Buffer contents:\n";
    for (i = 0; i < N; i++)
    {
        cout << pd5[i] << " at " << &pd5[i] << ";\n";
        cout << pd6[i] << " at " << &pd6[i] << ";\n";
    }
    delete[] pd1;
    delete[] pd3;

    return 0;
}
