#ifndef BULK_QUOTE_H
#define BULK_QUOTE_H

#include "Quote.h"
#include "Disc_quote.h"

class Bulk_quote: public Disc_quote
{
public:

    // Bulk_quote() = default;
    // Bulk_quote(const std::string&, double, std::size_t, double);

    using Disc_quote::Disc_quote; // inherit Disc_quote's constructors

    // copy constructor
    Bulk_quote(const Bulk_quote &bq):Disc_quote(bq)
    {std::cout << "Bulk_quote : copy constructor\n";}
    // move constructor
    Bulk_quote(Bulk_quote&& bq) noexcept : Disc_quote(std::move(bq))
    {std::cout << "Bulk_quote : move constructor\n";}
    // copy =()
    Bulk_quote& operator =(const Bulk_quote& rhs)
    {
        Disc_quote::operator =(rhs);
        std::cout << "Bulk_quote : copy =()\n";
        return *this;
    }
    // move =()
    Bulk_quote& operator =(Bulk_quote&& rhs) noexcept
    {
        Disc_quote::operator =(std::move(rhs));
        std::cout << "Bulk_quote : move =()\n";
        return *this;
    }

    // overrides the base version in order to implement the bulk purchase discount policy
    double net_price(std::size_t n) const override;

    Bulk_quote* clone() const & {return new Bulk_quote(*this);}
    Bulk_quote* clone() && {return new Bulk_quote(std::move(*this));}
    ~Bulk_quote() override
    {
        std::cout << "destructing Bulk_quote\n";
    }

};


/// old
// class Bulk_quote: public Quote
// {
// private:
//     std::size_t min_qty = 0; // minimum purchase for the discount to apply.
//     double discount = 0.0; // fractional discount to apply
// public:

//     Bulk_quote() = default;
//     Bulk_quote(const std::string&, double, std::size_t, double);
//     // overrides the base version in order to implement the bulk purchase discount policy
//     double net_price(std::size_t n) const override;
// };

#endif