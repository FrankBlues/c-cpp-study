#include <iostream>
#include <cstdlib>
#include "sales_data.h"
using namespace std;

// Ex1816
namespace Exercise {
    int ivar = 0;
    double dvar = 0;
    const int limit = 1000;
}
int ivar = 0;

// Ex191
void *operator new(size_t size) {
    if (void *mem = malloc(size))
        return mem;
    else
        throw bad_alloc();
}
void operator delete(void *mem) noexcept { free(mem); }


int main(int argc, char const *argv[])
{
    // sales_data::Sales_data item1, item2, sum;
    // while (cin >> item1 >> item2) { // read two transactions
    //     try {
    //         sum = item1 + item2; // calculate their sum
    //     } catch (const exceptions::isbn_mismatch &e) {
    //         cerr << e.what() << ": left isbn(" << e.left
    //              << ") right isbn(" << e.right << ")" << endl;
    //     }
    // }

    // Ex1816
    // position 2
    // using namespace Exercise;
    // double dvar = 3.1416;
    // int iobj = limit + 1;
    // // ++ivar;  // ivar" is ambiguous
    // ++Exercise::ivar;
    // ++::ivar;
    // cout << dvar << " " << iobj << " " << Exercise::ivar << " " << ::ivar << endl;
    
    // ex191
    // string *s = ::new string("ssss");
    // cout << *s << " " << sizeof(*s) << endl;
    // ::delete s;

    // string s("aaa");
    // if (typeid(s) == typeid(string))
    //     cout << s << " " << typeid(s).name() <<endl;

    /// enumerate
    enum color {red, yellow, green}; // unscoped enumeration
    // enum stoplight {red, yellow, green}; // error: redefines enumerators
    enum class peppers {red, yellow, green}; // ok: enumerators are hidden
    color eyes = green; // ok: enumerators are in scope for an unscoped enumeration
    peppers p = peppers::green; // error: enumerators from peppers are not in scope
    // color::green is in scope but has the wrong type
    color hair = color::red; // ok: we can explicitly access the enumerators
    peppers p2 = peppers::red; // ok: using red from peppers

    return 0;
}
