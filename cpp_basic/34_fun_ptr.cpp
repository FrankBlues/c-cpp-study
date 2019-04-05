#include <iostream>

using namespace std;
double betsy(int);
double pam(int);

//pointer to a function
void estimate(int lines,double (*pf) (int));

int main(){
    int code;

    cout << "how many lines of code do you have?\n";
    cin >> code;
    cout << "Here's Betsy's estimate.\n";
    estimate(code,betsy); //函数作为参数，函数名为函数内存地址
    cout << "Here's Pam's estimate.\n";
    estimate(code,pam);
    return 0;
}

double betsy(int lns){
    return 0.05 * lns;
}
double pam(int lns){
    return 0.03 * lns + 0.0004 * lns * lns ;
}

//pointer to a function
void estimate(int lines,double (*pf) (int)){
    cout << lines << " lines will take ";
    cout << (*pf)(lines) << " hour (s) \n";
}
