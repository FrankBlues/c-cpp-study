#include <iostream>
#include<string>
using std::string;
using namespace std;
// 返回指向包含10个字符串的数组的指针 P232
// 不使用类型别名或decltype
string (*arr_func(int i))[10];
// 使用类型别名
typedef string sArr[10];
sArr *arr_func(int i);

//使用尾置返回类型
auto func(int i) -> string(*)[10];

//使用decltype
string str_arr[10] = {"my", "name", "is", "meng", "limeng", ",", "and", "you", "", ""};
decltype(str_arr) *func(int i);


int main()
{
   
   cout << endl;
   return 0;
}