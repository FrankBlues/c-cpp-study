#include <iostream>
using namespace std;

int main()
{
    constexpr size_t rowCnt = 3, colCnt = 4; // 必须是常量
    int arr[rowCnt][colCnt] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

    int(&row)[4] = arr[1]; // 引用原数组第二行

    // 指针方式访问 或者 p=begin(arr)
    for (auto p = arr; p != arr + rowCnt; ++p) // 指向第一行，是一个数组
    {
        // cout << *p << endl;
        for (auto q = *p; q != *p + colCnt; ++q) // *p是数组, q=*p是首地址
        {
            cout << *q;
        }
    }

    // for in 方式访问
    // for (auto &row : arr)  // 外层必须用引用, 否则转换成指针
    // {
    //     for (auto col : row)
    //     {
    //         cout << col;
    //     }
    // }

    // for (size_t i = 0; i != rowCnt; ++i) // 下标方式访问数组
    // {
    //     for (size_t j = 0; j != colCnt; ++j)
    //     {
    //         cout << arr[i][j];
    //     }
    // }

    cout << endl;
}