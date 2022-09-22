#include<iostream>
using namespace std;
#include "sales_data.h"

namespace sales_data{
    // 定义在类外的构造函数
    Sales_data::Sales_data(std::istream &is)
    {
        read(is, *this);
    }

    // 类成员函数avg_price combine定义(Sales_data::)
    double Sales_data::avg_price() const
    {
        // 隐式地使用了Sales_data成员
        if (units_sold)
            return revenue/units_sold;
        else
            return 0;
    }

    Sales_data& Sales_data::combine(const Sales_data &rhs)
    {
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
        return *this;  // 返回调用该函数的对象
    }

    // 类非成员函数
    istream& read(istream &is, Sales_data &item)
    {
        double price = 0;
        is >> item.bookNo >> item.units_sold >> price;
        item.revenue = price * item.units_sold;
        return is;
    }

    istream& operator>>(istream &is, Sales_data &item)
    {
        double price = 0;
        is >> item.bookNo >> item.units_sold >> price;
        if (is)  // check that the inputs succeeded
            item.revenue = price * item.units_sold;
        else
            item = Sales_data(); // input failed: give the object the default state
        return is;
    }

    // IO类不能被拷贝，只能通过引用的方式调用
    ostream &print(ostream &os, const Sales_data &item)
    {
        os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
        return os;
    }

    std::ostream &operator<<(std::ostream &os, const Sales_data &item)
    {
        os << item.isbn() << " " << item.units_sold << " "
        << item.revenue << " " << item.avg_price();
        return os;
    }

    Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
    {
        Sales_data sum = lhs;
        sum.combine(rhs);
        return sum;
    }

    Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
    {
        Sales_data sum(lhs);  // copy data members from lhs into sum
        sum += rhs;  // add rhs into sum
        return sum;
    }

    bool operator==(const Sales_data &lhs, const Sales_data &rhs)
    {
        return lhs.isbn() == rhs.isbn() &&
        lhs.units_sold == rhs.units_sold &&
        lhs.revenue == rhs.revenue;
    }

    bool operator!=(const Sales_data &lhs, const Sales_data &rhs)
    {
        return !(lhs == rhs);
    }

    Sales_data& Sales_data::operator+=(const Sales_data &rhs)
    {
        if (isbn() != rhs.isbn())
            throw exceptions::isbn_mismatch("wrong isbns", isbn(),
            rhs.isbn());
        units_sold += rhs.units_sold;
        revenue += rhs.revenue;
        return *this;
    }
}