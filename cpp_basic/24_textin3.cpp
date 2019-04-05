#include <iostream>

using namespace std;

int main()
{
    cout << "Enter character:";
    int count = 0;
    char ch;
    cin.get(ch);
    //while ( !cin.fail()){
    //while (!cin.eof()){
    while (cin){
    //while (cin.get(ch)){
        cout << ch;
        ++count;
        cin.get(ch);

    }

    cout << endl << count << " characters read\n";

    cout << "done.\a\n";

    return 0;
}


