#ifndef QUOTE_H
#define QUOTE_H
#include <iostream>
#include <string>

class Quote
{
    friend bool operator==(const Quote &q1, const Quote &q2);
    friend bool operator!=(const Quote &q1, const Quote &q2);
    friend double print_total(std::ostream&, const Quote&, std::size_t n);
private:
    std::string bookNo; // ISBN number of this item
protected:
    double price = 0.0; // normal, undiscounted price
public:
    Quote() = default;
    Quote(const std::string &book, double sales_price):
        bookNo(book), price(sales_price) { }
    
    // copy constructor
    Quote(const Quote &q):bookNo(q.bookNo), price(q.price)
    {std::cout << "Copy constructor of class Quote" << std::endl;}
    // move constructor 
    Quote(Quote &&q) noexcept:bookNo(std::move(q.bookNo)), price(std::move(q.price))
    {std::cout << "Move constructor of class Quote" << std::endl;}

    // copy=
    Quote & operator=(const Quote &q)
    {
        if (*this != q)
        {
            bookNo = q.bookNo;
            price = q.price;
        }
        std::cout << "Quote: copy =() \n";
        return *this;
    }

    // move =
    Quote& operator =(Quote&& rhs)  noexcept
    {
        if(*this != rhs)
        {
            bookNo = std::move(rhs.bookNo);
            price  = std::move(rhs.price);
        }
        std::cout << "Quote: move =!!!!!!!!! \n";

        return *this;
    }

    

    std::string isbn() const { return bookNo; }
    // returns the total sales price for the specified number of items
    // derived classes will override and apply different discount algorithms
    virtual double net_price(std::size_t n) const
    { return n * price; }
    virtual void print_mem(std::ostream &os) const
    {os << "ISBN: " << bookNo << "\tprice: "<< price;}
    // virtual function to return a dynamically allocated copy of itself
    // these members use reference qualifiers; see §13.6.3 (p. 546)
    virtual Quote* clone() const & {return new Quote(*this);}
    virtual Quote* clone() && {return new Quote(std::move(*this));}
    virtual ~Quote(){std::cout << "destructing Quote\n";} // dynamic binding for the destructor

};

bool inline operator==(const Quote &q1, const Quote &q2)
{
    return q1.bookNo == q2.bookNo;
}

bool inline operator!=(const Quote &q1, const Quote &q2)
{
    return !(q1 == q2);
}

double inline print_total(std::ostream &os, const Quote &item, std::size_t n)
{
    double ret = item.net_price(n);
    os << "ISBN:" << item.isbn()
       << "# sold: " << n << " total due: " << ret << std::endl;
    return ret;
}



#endif