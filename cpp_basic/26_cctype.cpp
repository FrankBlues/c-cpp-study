#include <iostream>
#include <cctype> //protypes for character functions
using namespace std;

int main(){
    cout << "enter text, end with @ \n";
    char ch;
    int whitespace = 0;
    int digits = 0;
    int chars = 0;
    int punct = 0;
    int others = 0;

    cin.get(ch);
    while (ch != '@'){
        if (isalpha(ch)) //字母
            chars++ ;
        else if (isspace (ch)) //空格
            whitespace++;
        else if (isdigit (ch)) //标点
            digits++;
        else if (ispunct(ch))
            punct++;
        else;
            others++;
        cin.get(ch);

    }
    cout << chars << " letters,"
        << whitespace << " whitespace,"
        << digits << " digits,"
        << punct << " punct,"
        << others << " others.\n";


    return 0;
}