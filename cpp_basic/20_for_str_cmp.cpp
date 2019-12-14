#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{

    //char str[] = "?ate"; // c style
    string str = "?ate";

    char ch;

    //for (ch = 'a' ; strcmp(str,"mate") != 0 ; ch ++ ){ // c style
    for (ch = 'a'; str != "mate"; ch++)
    { // c++ style  use !=
        //swap
        cout << "str is " << str << endl;
        str[0] = ch;
    }

    cout << "Finally the word is " << str;

    return 0;
}
