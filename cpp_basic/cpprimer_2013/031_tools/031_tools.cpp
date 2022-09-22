#include <iostream>
#include "sales_data.h"
using namespace std;

// Ex1816
namespace Exercise {
    int ivar = 0;
    double dvar = 0;
    const int limit = 1000;
}
int ivar = 0;


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
    using namespace Exercise;
    double dvar = 3.1416;
    int iobj = limit + 1;
    // ++ivar;  // ivar" is ambiguous
    ++Exercise::ivar;
    ++::ivar;
    cout << dvar << " " << iobj << " " << Exercise::ivar << " " << ::ivar << endl;
    return 0;
}
