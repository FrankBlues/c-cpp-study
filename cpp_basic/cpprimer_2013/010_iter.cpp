#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
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
		
	vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for(auto it = nums.begin(); it != nums.end(); ++ it)
    {
        *it = (*it) *2;
        cout << *it << " ";
    }
    cout << endl;
    return 0;
}