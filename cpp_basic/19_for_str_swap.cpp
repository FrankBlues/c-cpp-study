#include <iostream>
#include <string>
using namespace std;

int main()
{
    cout << "Enter a string :";
    string str;
    cin >> str;

    char temp;

    int i, j;
    for (j = 0, i = str.size() - 1; j < i; --i, ++j)
    {
        //swap
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }

    cout << "Now the word is " << str;

    return 0;
}
