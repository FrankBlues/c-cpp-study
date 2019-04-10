#include <iostream>
#include <cstring>
using namespace std;

int main()
{
    char animal[20] = "bear"; //
    const char *bird = "wren";
    char *ps; // uninitialized

    cout << "animal is " << animal << endl; //传递首地址
    cout << "bird is " << bird << endl;
    //cout << ps; //wrong usage

    cout << "Enter animal : ";
    cin >> animal;

    ps = animal; //set ps point to string

    cout << "ps is now :" << ps << endl;

    cout << "before using strcpy , \n"
         << "animal location is " << (int *)animal << endl //默认显示字符，转换后才可以显示内存地址
         << "ps location is " << (int *)ps << endl;

    ps = new char[strlen(animal) + 1]; // alloc new mem
    strcpy(ps, animal);
    cout << "after using strcpy , \n"
         << animal << " at " << (int *)animal << endl
         << ps << " at " << (int *)ps << endl;

    delete[] ps;
    return 0;
}
