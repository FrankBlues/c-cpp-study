#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    const int size = 15; // array initial cannot be variable
    char name1[size];
    char name2[size] = "c++owboy";
    cout << "input name1:";
    //cin >> name1;
    //cin.getline(name1,size); //read line
    cin.get(name1,size).get(); // get string new line
    cin.get(name1,size).get();
    cout << "name1 is " << name1 << endl;
    cout << "length of name1 is " << strlen(name1) << endl;
    cout << "size of name1 is " << sizeof(name1) << endl;
    name2[3] = '\0';
    cout << "first 3 char of name2 is " << name2 <<endl;
    

    return 0;
}
