#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <cctype>

int main()
{
    string s("some string");

    if (s.begin() != s.end()) // 判断不为空
    {
        for (auto it = s.begin(); it != s.end() && !isspace(*it); ++it) // 迭代的方式访问
            *it = toupper(*it);
    }

    // for (auto a : s)
    //     cout << a;
    for (auto it = s.begin(); it != s.end(); ++it) //(*it).empty() 相当于 it -> empty()
    {
        cout << *it;
    }

    cout << endl;
    return 0;
}