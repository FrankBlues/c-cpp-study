#include <iostream>
#include <ctime>
using namespace std;

int main()
{
    cout << "Enter the delay time, in seconds :";
    float sec;
    cin >> sec;

    cout << "CLOCKS_PER_SEC : " << CLOCKS_PER_SEC << endl;
    clock_t delay = sec * CLOCKS_PER_SEC;

    cout << "starting \a\n";
    clock_t start = clock();
    while (clock() - start < delay)
        ;
    cout << "done.\a\n";

    return 0;
}


