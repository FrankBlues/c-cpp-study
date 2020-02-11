#ifndef SALES_DATA_H //头文件保护符
#define SALES_DATA_H
#include <string>
struct sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};
#endif