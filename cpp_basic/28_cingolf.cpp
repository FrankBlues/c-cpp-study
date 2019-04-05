#include <iostream>

using namespace std;

const int Max = 5;

int main(){
    double golf[Max];
    cout << "enter  5 numbers,  \n";

    
    int i;

    for (i = 0 ; i < Max ; i++ ){
        cout << "golf #" << i+1 << ": ";
        while(!(cin >> golf[i])){ //处理错误输入
            cin.clear(); //reset input
            while (cin.get() != '\n')
                continue;
            cout << "enter a number :";
        }

    }

    //average
    double total = 0.0;
    for (int j = 0; j < Max ; j++){
        total += golf[j];
    }
    cout << "total is " << total << endl;
    cout << "i = " << i <<endl;

    cout << "average of golf = " << total / i << endl;

    return 0;
}