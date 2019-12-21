#include <iostream>
#include "sales_data.h"

using namespace std;

int main()
{
    double price = 0;
    sales_data data1, data2;
    cin >> data1.name >> data1.numbers >> data1.price;
    double data1_revenue = data1.numbers * data1.price;
    cout << data1_revenue;
    cout << endl;
    return 0;
}
