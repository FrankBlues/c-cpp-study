#include <iostream>

using namespace std;

int main()
{
    char c = 'M';
    int i = c;
    cout << "character " << c << " sascii code is: " << i << endl;
    cout << "dispaly char using cout.put():" << endl;
    cout.put(c);
    cout << endl;
    cout << "display ! directly using cout << :" << '!' << endl;
    cout << "display ! using cout.put():";
    cout.put('!');
    cout << endl;
    return 0;
}
