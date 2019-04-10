#include <iostream>

using namespace std;

int main()
{

    short *a_arr = new short[15];

    a_arr[0] = 23; //数组指针名直接访问数组
    a_arr[1] = 32;
    a_arr[2] = 89;

    cout << "a_arr[1] = " << a_arr[1] << endl;
    cout << "location: " << a_arr << endl;
    a_arr = a_arr + 1; // 不是数值加1，而是位置前进1个，根据内容占用内存长度而不同
    cout << "Now location = " << a_arr << endl;
    cout << "Now a_arr[0] = " << a_arr[0] << endl
         << "a_arr[1] = " << a_arr[1] << endl;

    a_arr = a_arr - 1; // point back
    delete[] a_arr;    // 删除数组指针
    return 0;
}