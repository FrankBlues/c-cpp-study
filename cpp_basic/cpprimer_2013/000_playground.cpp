#include <iostream>
int main()
{
    int a = 3, b = 4;
    decltype(a) c = a;
    decltype(a = b) d = a;
    ++c;
    ++d;
    std::cout << a << std::endl;
    return 0;
}