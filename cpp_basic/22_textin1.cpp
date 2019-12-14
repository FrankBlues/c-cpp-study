#include <iostream>

using namespace std;

int main()
{
    cout << "Enter character, end with # :";
    int count = 0;
    char ch;
    cin >> ch;
    while (ch != '#'){
        cout << ch;
        ++count;
        cin >> ch;

    }

    cout << endl << count << " characters read\n";

    cout << "done.\a\n";

    return 0;
}


