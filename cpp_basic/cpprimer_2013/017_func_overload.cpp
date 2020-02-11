#include<string>
using std::string;

// 比较两个string的长度，返回较短的那个引用，返回常量引用
const string &shorterString(const string &s1, const string &s2)
{
    return s1.size() < s2.size() ? s1 : s2;
}

// 通过const_cast转换成普通的引用
string &shorterString(string &s1, string &s2)
{
    auto &r = shorterString(const_cast<const string&>(s1),
                            const_cast<const string&>(s2));
    return const_cast<string&>(r);
}