
#include <iostream>
#include <string>
using std::string;

using namespace std;

int main()
{
    string word, line; // 默认初始化， 空字符串
    // while (cin >> word)
    while (getline(cin, line))
    {
        if (!line.empty())
            cout << line << endl;
        if (!line.size() > 80)
            cout << line << endl;
    }
    cout << endl;
    return 0;
}