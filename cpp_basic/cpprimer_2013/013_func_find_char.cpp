#include <iostream>
using namespace std;
#include <string>
using std::string;

// s中c第一次出现的次数;
// 统计c 出现的总次数
// 用引用避免拷贝
string::size_type find_char(const string &s, char c,
                            string::size_type &cnt)
{
    auto set = s.size();
    cnt = 0;
    for (decltype(set) i = 0; i != s.size(); ++i)
    {
        if (s[i] == c)
        {
            if (set == s.size())
                set = i;
            ++cnt; // 统计出现的次数
        }
    }
    return set;
}

int main()
{
    string str("some string!");
    string::size_type f, cnt;
    f = find_char(str, 's', cnt);
    cout << f << ' ' << cnt;
    cout << endl;
}