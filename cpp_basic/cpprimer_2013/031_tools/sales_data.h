#ifndef SALES_DATA_H //头文件保护符
#define SALES_DATA_H
#include <string>
// template <class T> class std::hash; // needed for the friend

// 使用struct或class都可以
// struct Sales_data 两者访问权限不太一样
namespace sales_data{
    class Sales_data
    {
        friend class std::hash<Sales_data>;
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

    
}

// open the std namespace so we can specialize std::hash
namespace std {
    template <> // we're defining a specialization with
    struct hash<sales_data::Sales_data> // the template parameter of Sales_data
    {
        // the type used to hash an unordered container must define these types
        typedef size_t result_type;
        typedef sales_data::Sales_data argument_type; // by default, this type needs ==
        size_t operator()(const sales_data::Sales_data& s) const;
        // our class uses synthesized copy control and default constructor
    };

    inline
    size_t hash<sales_data::Sales_data>::operator()(const sales_data::Sales_data& s) const
    {
        return hash<string>()(s.bookNo) ^
               hash<unsigned>()(s.units_sold) ^
               hash<double>()(s.revenue);
    }

}

// hypothetical exception classes for a bookstore application
namespace exceptions {
    class out_of_stock: public std::runtime_error {
    public:
        explicit out_of_stock(const std::string &s):
            std::runtime_error(s) { }
    };

    class isbn_mismatch: public std::logic_error {
    public:
        explicit isbn_mismatch(const std::string &s):
            std::logic_error(s) { }
        isbn_mismatch(const std::string &s,
            const std::string &lhs, const std::string &rhs):
            std::logic_error(s), left(lhs), right(rhs) { }
        const std::string left, right;
    };
}

#endif