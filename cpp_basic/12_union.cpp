#include <iostream>

using namespace std;

int main()
{
    struct widget
    {
        string brand;
        int type;
        union id { //存储多种类型，但只能有一种生效
            long id_num;
            char id_char[20];
        } id_val;
    } w1;

    w1.brand = "aws";
    cout << "input type(int) :";
    cin >> w1.type;
    if (w1.type == 1)
    {
        cout << "input id(num): ";
        cin >> w1.id_val.id_num;
    }
    else
    {
        cout << "input id(char): ";
        cin >> w1.id_val.id_char;
    }

    cout << "size of id_val: " << sizeof(w1.id_val) << endl;
    cout << "content of id_val: " << endl;
    if (w1.type == 1)
    {
        cout << w1.id_val.id_num;
    }
    else
    {
        cout << w1.id_val.id_char;
    }

    return 0;
}
