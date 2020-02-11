#include <iostream>
using namespace std;
#include "sales_data.h"

int main(int argc, char const *argv[])
{
    Sales_data total;
    if (read(cin, total))
    {
        Sales_data trans;
        while (read(cin, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(cout, total) << endl;
                total = trans;
            }
        }
        print(cout, total) << endl;
    }
    else
    {
        cerr << "No data?!" << endl;
    }
    return 0;
}
