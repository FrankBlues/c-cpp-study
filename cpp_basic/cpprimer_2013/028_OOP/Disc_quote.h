#ifndef DISK_QUOTE_H
#define DISK_QUOTE_H

#include "Quote.h"

//We may not create objects of a type that is an abstract base class
class Disc_quote: public Quote
{
protected:
    std::size_t quantity = 0; // purchase size for the discount to apply
    double discount = 0.0; // fractional discount to apply
public:
    Disc_quote() = default;
    Disc_quote(const std::string& book, double price, 
        std::size_t qty, double disc): 
        Quote(book, price), quantity(qty), discount(disc) { }
    double net_price(std::size_t n) const = 0;  // pure virtual function 
};


#endif