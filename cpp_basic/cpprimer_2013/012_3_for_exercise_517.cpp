#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> int_arr1 = {0, 1, 1, 2};
    vector<int> int_arr2 = {0, 1, 1};
    bool is_prefix = true;
    for(auto beg1 = int_arr1.begin(), beg2 = int_arr2.begin(); 
        beg1 != int_arr1.end() && beg2 != int_arr2.end(); ++ beg1, ++beg2)
    {
        if(*beg1 != *beg2)
        {
            is_prefix = false;
            break;
        }
    }
    cout << is_prefix << endl;

    return 0;
}