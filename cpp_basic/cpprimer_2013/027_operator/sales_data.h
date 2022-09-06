#ifndef SALES_DATA_H //头文件保护符
#define SALES_DATA_H
#include <string>
// 使用struct或class都可以
// struct Sales_data 两者访问权限不太一样
class Sales_data
{
    // 为Sales_data的非成员函数所做的友元声明
    friend Sales_data add(const Sales_data &, const Sales_data &);
    friend Sales_data operator+(const Sales_data &, const Sales_data &);
    friend std::ostream &print(std::ostream &, const Sales_data &);
    friend std::ostream &operator<<(std::ostream &, const Sales_data &);
    friend std::istream &read(std::istream &, Sales_data &);
    friend std::istream &operator>>(std::istream &, Sales_data &);

    friend bool operator==(const Sales_data &, const Sales_data &);
    friend bool operator!=(const Sales_data &, const Sales_data &);

public: // 添加访问说明符
    // 新增构造函数
    Sales_data() = default; // 保留默认构造函数
    // explicit 阻止构造函数隐式创建该类，只能在声明时使用，只能用于一个实参的函数；
    explicit Sales_data(const std::string &s) : bookNo(s) {}
    Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p * n) {}
    explicit Sales_data(std::istream &);
    // 新成员 操作
    std::string isbn() const { return bookNo; } // const 修改隐式this指针的类型
    // std::string isbn() const {return this->bookNo;}
    Sales_data &combine(const Sales_data &);

    Sales_data& operator+=(const Sales_data &);  // should, be defined as members

private: // 访问说明符
    double avg_price() const;

    // 数据成员
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
// 非成员接口函数
Sales_data add(const Sales_data &, const Sales_data &);
std::ostream &print(std::ostream &, const Sales_data &);
std::istream &read(std::istream &, Sales_data &);
#endif