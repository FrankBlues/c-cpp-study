#include <iostream>
using namespace std;

// 传递指针进行数组操作
void print(const int *begin, const int *end)
{
    while(begin != end)
    {
        cout << *begin++ << endl;
    }
}

// 传递引用
void print(int (&a)[12]) // 目前是固定数组
{
    for (auto elem : a)
    {
        cout << elem << endl;
    }
}

int main()
{
    int arr[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    // print(arr, arr+12);
    // print(begin(arr), end(arr));
    print(arr);
    return 0;
}