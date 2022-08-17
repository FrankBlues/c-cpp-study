#include <iostream>
#include <string>
using namespace std;

int main()
{
    string s, curStr, maxStr;
    unsigned occurence = 0, maxOcc = 1;
    unsigned firstFlag = 0;
    while(cin >> s && !s.empty())
    {
        if (firstFlag == 0)
        {
            curStr =s;
            ++firstFlag;
        }

        if (curStr == s)
        {
            ++occurence;
        } else {
            if (occurence > maxOcc)
            {
                maxOcc = occurence;
                maxStr = curStr;
            }
            // cout << curStr << " occurs " << occurence << " times" << endl;
            curStr = s;
            occurence = 1;
        }
    }
    if (occurence > maxOcc)
    {
        maxOcc = occurence;
        maxStr = curStr;
    }

    if (maxOcc > 1)
        cout << maxStr << " occurs " << maxOcc << " times" << endl;
    else
        cout << "no word was repeated!\n";
    return 0;
}