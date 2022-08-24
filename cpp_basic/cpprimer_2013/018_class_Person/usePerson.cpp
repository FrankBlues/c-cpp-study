#include <iostream>
#include "Person.h"
using namespace std;
int main()
{
    Person p("mike");
    Person p1("nike", "beijing");
    Person p2("jim", "beijing", 27);
    // Person p3(cin);
    // read(std::cin, p);
    print(std::cout, p);
    cout << endl;
    print(std::cout, p1);
    cout << endl;
    return 0;
}