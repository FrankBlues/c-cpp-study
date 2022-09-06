#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
using namespace std;
#include "sales_data.h"


void salesDataTest()
{
    Sales_data total;
    if (read(cin, total))
    {
        Sales_data trans;
        while (read(cin, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                // print(cout, total) << endl;
                cout << total << endl;
                total = trans;
            }
        }
        // print(cout, total) << endl;
        cout << total << endl;
    }
    else
    {
        cerr << "No data?!" << endl;
    }
}

struct exercise1434  // Function-Call Operator
{
    const int operator()(bool con, const int result1, const int result2) const
    {
        return con?result1:result2;
    }
};

class exercise1435  // Function-Call Operator read string
{
public:
    exercise1435() = default;
    exercise1435(istream &is): is(is){}
    const string operator()()
    {
        string s;
        getline(is, s);
        return s;
    }
private:
    istream &is;
};


int add(int i, int j){ return i + j; }
auto mod = [](int i, int j){ return i % j; };
struct Div{ int operator ()(int i, int j) const { return i / j; } };
void exercise1444()
{
    int (*fp)(int, int) = add;  // add 与 sales_data成员函数冲突
    auto binops = std::map<std::string, std::function<int(int, int)>>
{
    { "+", fp },                               // function pointer 
    { "-", std::minus<int>() },                 // library functor 
    { "/", Div() },                             // user-defined functor 
    { "*", [](int i, int j) { return i*j; } },  // unnamed lambda 
    { "%", mod }                                // named lambda object 
};
    cout << binops["+"](1, 2) << endl;
    cout << binops["-"](9, 2) << endl;
}


int main(int argc, char const *argv[])
{
    exercise1434 e1314;
    // cout << e1314(1 < 2, 3, 2) << endl;

    vector<string> svec;
    // exercise1435 e1435(cin);
    // for ( std::string tmp; !( tmp = e1435() ).empty(); ) svec.push_back( tmp );
    // for (const auto &str : svec) std::cout << str << " ";
    // std::cout << std::endl;

    exercise1444();
    
    return 0;
}
