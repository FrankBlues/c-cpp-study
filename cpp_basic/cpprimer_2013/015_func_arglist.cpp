#include <iostream>
using namespace std;
// 形参列表 同一类型
int sum_all(initializer_list<int> a)
{
    int sum = 0;
    for (auto i : a)
    {
        sum += i;
    }
    return sum;
}

int main()
{
   initializer_list<int> a({1, 2, 3, 4, 5});
   cout << sum_all(a);
   cout << endl;
   return 0;
}