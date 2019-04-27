#include <iostream>
#include "sales_data.h"

int main()
{
    sales_data book1, book2;
    book1.name = 'a';
    book1.price = 15.9;
    book1.numbers = 5;
    book2.name = 'b';
    book2.price = 19.9;
    book2.numbers = 4;
    std::cout << "book1 and book2 total sales:"
              << book1.price * book1.numbers + book2.price * book2.numbers
              << std::endl;
    return 0;
}
