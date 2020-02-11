#include <iostream>
#include "Screen.h"
#include "Window_mgr.h"
using std::cout;
int main(int argc, char const *argv[])
{
    Screen myscreen;
    char ch = myscreen.get();
    // char ch = myscreen.get(0, 0);
    myscreen.move(4, 0).set('#');
    cout << ch << std::endl;
    Window_mgr wmgr;
    return 0;
}
