//variable with external and internal linkage
#include <iostream>
int tom = 3;
int dict = 30;
static int harry = 300; // static,internal linkage

void remote_access();

int main()
{
    using namespace std;
    cout << "main() reports the following addresses: \n";
    cout << &tom << " = &tom, " << &dict << " = &dick, ";
    cout << &harry << " = &harry\n";
    remote_access();
    return 0;
}
