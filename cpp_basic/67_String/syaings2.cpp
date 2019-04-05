// use pointers to object

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "String1.h"

const int ArSize = 10;
const int MaxLen = 81;

int main(int argc, char const *argv[])
{
    using std::cin;
    using std::cout;
    using std::endl;
    String1 name;
    cout << "Input name : ";
    cin >> name;

    cout << name << ", enter up to " << ArSize
         << " short sayings ,<empty line to quit >:\n";
    String1 sayings[ArSize];
    char temp[MaxLen];
    int i;
    for (i = 0; i < ArSize; i++)
    {
        cout << i + 1 << ": ";
        cin.get(temp, MaxLen);
        while (cin && cin.get() != '\n')
            continue;
        if (!cin || temp[0] == '\0')
            break;
        else
            sayings[i] = temp;
    }
    int total = i;

    cout << " Here are your sayings: \n";
    for (i = 0; i < total; i++)
        cout << sayings[i][0] << ": " << sayings[i] << endl;
    
    // use pointers to track 
    String1 * shortest = &sayings[0]; //initialize to first object
    String1 * first = &sayings[0];

    for (i = 1 ; i< total ; i++)
    {
        if (sayings[i].length() < shortest->length())
            shortest = &sayings[i];
        if (sayings[i] < *first)
            first = &sayings[i];
    }

    cout << "Shortest saying: \n"
         << *shortest << endl;
    cout << "First alphabetically: \n"
         << *first << endl;
    
    srand(time(0));
    int choice = rand()%total;

    //use new to create
    String1 * favorite = new String1(sayings[choice]);
    cout << "My favorite saying: \n" << *favorite << endl;
    delete favorite;

    return 0;
}
