//using Stock class main
#include <iostream>
#include "stock2.h"
const int STKS = 4;
int main()
{
    using std::cout;
    using std::ios_base;
    cout.setf(ios_base::fixed);
    cout.precision(2);
    cout.setf(ios_base::showpoint);

    Stock stocks[4] = {
        Stock("NanoSmart", 12, 20.0),
        Stock("Boffo Obj", 200, 2.0),
        Stock("Monolithic Obe", 130, 3.25),
        Stock("Fleep Ent", 60, 6.5)};

    cout << "Using constructors to create new objects\n";
    Stock stock1("NanaSmart", 12, 20.0);
    stock1.show();
    Stock stock2 = Stock("Boffo Objects", 2, 2.0);
    stock2.show();

    cout << "Stock holdings: \n";
    int st;
    for (st = 1; st < STKS; st++)
        stocks[st].show();

    Stock top = stocks[0];
    for (st = 1; st < STKS; st++)
        top = top.topval(stocks[st]);
    cout << "\nMost valuable holding:\n";
    top.show();

    cout << "Done\n";
    return 0;
}