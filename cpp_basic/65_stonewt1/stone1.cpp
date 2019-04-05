//user-defined conversions

#include <iostream>
using std::cout;
#include "stonewt1.h"

int main()
{
    Stonewt p(9, 2.8);
    double p_wt = p; // implicit conversion
    cout << " class Convert to double => ";
    cout << "p: " << p_wt << " pounds \n";
    cout << "Convert to int =>";
    cout << "p: " << int(p) << " pounds \n";

    return 0;
}
