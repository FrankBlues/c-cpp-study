#include <iostream>
extern int tom;
static int dict = 10; //overrides external dick
int harry = 200;      //external variable definition
                      // no conflict with twofile1 harry

void remote_access()
{
    using namespace std;
    cout << "remote_access() reports the following addresses:\n";
    cout << &tom << " = &tom, " << &dict << " = &dick, ";
    cout << &harry << " = &harry\n";
}
