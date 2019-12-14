#include <iostream>
#include <cstring>
using namespace std;

char *getname(void); //function protype

int main()
{
    char *name;

    name = getname();
    cout << name << " at " << (int *)name << endl;
    delete[] name; //mem freeed

    name = getname(); //reuse
    cout << name << " at " << (int *)name << endl;
    delete[] name; //mem freeed

    return 0;
}

char *getname()
{ //return pointer to new string
    char temp[80];
    cout << "Enter name :";
    cin >> temp;

    char *pn = new char[strlen(temp) + 1]; // 节省内存
    strcpy(pn, temp);

    return pn;
}
