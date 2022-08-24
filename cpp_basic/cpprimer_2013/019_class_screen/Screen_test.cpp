#include <iostream>
#include "Screen.h"
#include "Window_mgr.h"
using std::cout;
int main(int argc, char const *argv[])
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(4,0).set('#').display(cout);
    cout << "\n";
    myScreen.display(cout);
    cout << "\n";
    return 0;
}
