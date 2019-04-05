#include <iostream>

using namespace std;

struct inflatable{
    char name[20];
    float volume;
    double price;
};

int main()
{
    inflatable * ps = new inflatable;
    
    cout << "enter name of ps :";
    cin.get(ps -> name,20); //method 1 

    cout << "enter volume : ";
    cin >> (*ps).volume; //method 2

    cout << "enter price :";
    cin >> ps-> price;
    
    cout << "name of ps is " << (*ps).name << endl;
    cout << "volume of ps is " << ps->volume << endl;
    cout << "price of ps is " << ps->price << endl;

    delete ps;

    return 0;
}
