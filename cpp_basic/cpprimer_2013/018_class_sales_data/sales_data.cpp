#include<iostream>
using namespace std;
#include "sales_data.h"


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

// IO类不能被拷贝，只能通过引用的方式调用
ostream &print(ostream &os, const Sales_data &item)
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