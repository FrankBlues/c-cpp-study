#include <iostream>
using namespace std;

int main()
{
    char c;
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, other = 0;
    unsigned spaceCnt = 0, tabCnt = 0, newlineCnt = 0;
    cin >> noskipws;  // donot skip spaces
    while(std::cin >> c)
    {
        switch (c)
        {
            case 'a': case 'A':
                ++aCnt;
                break;
            case 'e': case 'E':
                ++eCnt;
                break;
            case 'i': case 'I':
                ++iCnt;
                break;
            case 'o': case 'O':
                ++oCnt;
                break;
            case 'u': case 'U':
                ++uCnt;
                break;
            case ' ':
                ++spaceCnt;
                break;
            case '\t':
                ++tabCnt;
                break;
            case '\n':
                ++newlineCnt;
                break;
            default:
                ++other;
        }
    }
    cout << "a count:" << aCnt << endl;
    cout << "e count:" << eCnt << endl;
    cout << "i count:" << iCnt << endl;
    cout << "o count:" << oCnt << endl;
    cout << "u count:" << uCnt << endl;
    cout << "space count:" << spaceCnt << endl;
    cout << "tab count:" << tabCnt << endl;
    cout << "newline count:" << newlineCnt << endl;

    return 0;
}