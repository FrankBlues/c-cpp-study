#include <iostream>
#include<string>
using std::string;
using namespace std;
// 返回指向包含10个字符串的数组的指针
string (*arr_func(int i))[10];  // 函数声明
typedef string sArr[10];
sArr *arr_func(int i);

int main()
{
   cout << endl;
   return 0;
}