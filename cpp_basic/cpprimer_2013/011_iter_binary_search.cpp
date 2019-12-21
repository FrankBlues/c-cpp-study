#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <vector>
using std::vector;

int main()
{
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sought;
    // cin >> "Plese input a number:" ;
    cin >> sought;
    auto beg = v.begin(), end = v.end();
    auto mid = v.begin() + (end - beg) / 2;

    while (mid != end && *mid != sought)
    {
        if (sought < *mid)
        {
            end = mid;
        }

        else
        {
            beg = mid + 1;
        }
        mid = beg + (end - beg) / 2;
    }

    cout << *mid;
    cout << endl;

    return 0;
}