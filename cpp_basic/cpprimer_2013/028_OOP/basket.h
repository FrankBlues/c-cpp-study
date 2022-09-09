#ifndef BASKET_H
#define BASKET_H

#include <iostream>
#include <memory>
#include <set>
#include "Quote.h"

class Basket
{
private:
    // function to compare shared_ptrs needed by the multiset member
    static bool compare(const std::shared_ptr<Quote> &lhs,
                        const std::shared_ptr<Quote> &rhs)
    { return lhs->isbn() < rhs->isbn(); }
    // multiset to hold multiple quotes, ordered by the compare member
    std::multiset<std::shared_ptr<Quote>, decltype(compare)*>
        items{compare};
public:
    // void add_item(const std::shared_ptr<Quote> &sale)
    // { items.insert(sale); }
    // redefine add_item so that it takes a Quote object
    void add_item(const Quote& sale) // copy the given object
    { items.insert(std::shared_ptr<Quote>(sale.clone())); }
    void add_item(Quote&& sale) // move the given object
    { items.insert(
    std::shared_ptr<Quote>(std::move(sale).clone())); }
    // prints the total price for each book and the overall total for all items in the basket
    double total_receipt(std::ostream&) const;
};


#endif