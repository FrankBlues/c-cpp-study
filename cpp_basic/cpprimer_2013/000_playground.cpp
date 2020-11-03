#include <iostream>
int main()
{
    int i = 0;
    int *const pq1 = &i;
    const int ci = 42;
    const int *p2 = &ci;
    const int *const p3 = p2;
    const int &r = ci;

    std::cout << a << std::endl;
    // std::cout << p << std::endl;
    return 0;
}