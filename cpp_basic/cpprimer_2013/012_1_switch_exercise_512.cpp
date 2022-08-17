#include <iostream>
using namespace std;

int main()
{
    char c;
    unsigned fFlag = 0;
    unsigned ffCnt = 0, flCnt = 0, fiCnt = 0;
    while(std::cin >> c)
    {
        switch (c)
        {
            case 'f':
            {
                if (fFlag == 0)
                        ++fFlag;
                else {  // fFlag == 1
                    ++ffCnt;
                }
                break;
            }
            case 'l':
                if (fFlag == 1)
                {
                    ++flCnt;
                    --fFlag;
                }
                break;
            case 'i':
                if (fFlag == 1)
                {
                    ++fiCnt;
                    --fFlag;
                }
                break;
            default:
                ;
        }
    }
    cout << "ff count:" << ffCnt << endl;
    cout << "fl count:" << flCnt << endl;
    cout << "fi count:" << fiCnt << endl;

    return 0;
}