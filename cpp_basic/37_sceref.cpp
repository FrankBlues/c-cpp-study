//define and using a reference
#include <iostream>

using namespace std;

int main(){
    int rats = 101;
    int & rodents = rats; // define a reference
    
    cout << "rats = " << rats;
    cout << ", rodents = " << rodents << endl;

    cout << "rats address = " << &rats;
    cout << ",rodents address = " << &rodents << endl;

    int bunnies = 50;
    rodents = bunnies; 

    cout << "bunnies = " << bunnies;
    cout << ", rats = " << rats; //同样发生变化
    cout << ", rodents = " << rodents << endl;

    cout << "bunnies address = " << &bunnies;
    cout << ",rodents address = " << &rodents << endl;
    return 0;
}

