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
		
		
		int ia[3][4];
    int v = 1;
    for(auto &row: ia)
    {
        for(auto &col: row)
        {
            col = v;
            ++v;
        }
    }
    // use a range for
    for(int (&row)[4]: ia)
    {
        for(int &col: row)
        {
            cout << col << " ";
        }
        cout << endl;
    }

    // use subscripts
    for(size_t row = 0; row < 3 ; ++row)
    {
        for(size_t col = 0; col < 4; ++col)
        {
            cout << ia[row][col] << " ";
        }
        cout << endl;
    }

    // use pointer
    for(int (*p)[4] = ia; p < ia + 3; ++p)
    {
        for(int *q = *p; q < *p + 4; ++q)
        {
            cout << *q << " ";
        }
        cout << endl;
    }

    using int_array = int[4];
    typedef int int_array[4];

    // use a range for
    for(auto &row: ia)
    {
        for(auto &col: row)
        {
            cout << col << " ";
        }
        cout << endl;
    }

    // use subscripts
    for(auto row = 0; row < 3 ; ++row)
    {
        for(auto col = 0; col < 4; ++col)
        {
            cout << ia[row][col] << " ";
        }
        cout << endl;
    }

    // use pointer
    for(int_array *p = ia; p < ia + 3; ++p)
    {
        for(int *q = *p; q < *p + 4; ++q)
        {
            cout << *q << " ";
        }
        cout << endl;
    }

    // use pointer
    for(auto *p = ia; p < ia + 3; ++p)
    {
        for(auto *q = *p; q < *p + 4; ++q)
        {
            cout << *q << " ";
        }
        cout << endl;
    }
}