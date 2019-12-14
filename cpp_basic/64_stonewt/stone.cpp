//user-defined conversions

#include <iostream>
using std::cout;
#include "stonewt.h"
void display(const Stonewt &st, int n);

int main()
{
    Stonewt p = 260;  //uses constructor to initialize 构造函数只有
    //一个参数时 可以这样初始化
    Stonewt w(285.7); //same as Stonewt w = 285.7;
    Stonewt t(21.8);

    cout << " The tenor weighted ";
    p.show_stn();
    cout << "The detective weighted ";
    w.show_stn();
    cout << "The president weighted ";
    t.show_stn();
    p = 265.8; //uses constructor for conversion
    t = 325; //double first then to Stonewt
    cout << "After dinner,the tenor weighted ";
    t.show_stn();
    cout << "After dinner, The president weighted ";
    t.show_lbs();
    display(t, 2);
    cout << "The wrestler weighted even more. \n";
    display(422, 2); //将422转换为double类型 然后转化为Stonewt类
    cout << "No stone left unearned \n";

    return 0;
}

void display(const Stonewt &st, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "WoW! ";
        st.show_stn();
    }
}