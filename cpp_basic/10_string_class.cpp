#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
    int size = 15;
    string name1;
    string name2, name3;
    cout << "input name1 and name2:";
    //cin >> name1;
    //cin.getline(name1,size); //read line
    getline(cin, name1); // not cin.getline(a,b)
    getline(cin, name2);
    cout << "name1 + name2 =  " << name1 + name2 << endl;
    name3 = name1 + name2;
    cout << "length of name1 is " << name1.size() << endl; //not strlen() which is c style used for array like
    cout << "size of name1 is " << sizeof(name1) << endl;
    cout << "size of name2 is " << sizeof(name2) << endl;
    cout << "size of name3 is " << sizeof(name3) << endl;
    name1 += name2;
    cout << "name1 += name2 : " << name1 << endl;

    return 0;
}
