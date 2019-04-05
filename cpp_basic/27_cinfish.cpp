#include <iostream>

using namespace std;

const int Max = 5;

int main(){
    double fish[Max];
    cout << "enter up to 5 numbers,  \n";

    cout << "fish #1: ";
    int i =0;

    while (i < Max && (cin >> fish[i])){ //如果输入错误类型，停止
        cout << fish[i] << endl;
        if (++i < Max)
            cout << "fish #"<< i +1<< ": "  ;
    }

    //average
    double total = 0.0;
    for (int j = 0; j < Max ; j++){
        total += fish[j];
    }
    cout << "total is " << total << endl;
    cout << "i = " << i <<endl;
    if (i == 0)
        cout << "nofish.\n";
    else
        cout << "average of fish = " << total / i << endl;

    return 0;
}