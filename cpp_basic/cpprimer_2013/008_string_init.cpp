
#include <iostream>
#include <string>
using std::string;
using namespace std;

int main()
{
    string s1;          // 默认初始化， 空字符串
    string s2(s1);      // s1的副本
    string s2 = s1;     // 等价
    string s3 = "hiya"; // 字面值的副本
    string s3("hiya");  // 等价
    int n = 4;
    string s4(n, 'c'); // n个字符的重复
    cout << endl;
}