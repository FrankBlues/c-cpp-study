#include <iostream>

using namespace std;

struct inflatable
{
    char name[20];
    float volume;
    double price;
};

int main()
{
    inflatable guest = {
        "Go GGG",
        1.88,
        29.99};
    inflatable pal = {
        "Po PPP",
        2.88,
        28.99};

    cout << "name of guest " << guest.name << endl;
    cout << "volume of guest " << guest.volume << endl;
    inflatable guests[2] = {guest, pal}; //用于数组
    cout << "name of guest " << guests[0].name << endl;
    cout << "name of pal " << guests[1].name << endl;
    return 0;
}
