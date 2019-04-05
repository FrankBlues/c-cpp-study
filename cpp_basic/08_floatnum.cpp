#include <iostream>

using namespace std;

int main()
{
    cout.setf(ios_base::fixed,ios_base::floatfield);//fixed-point
    float f = 10.0/3.0;  //至少保证6个有效位 
    double d = 10.0/3.0; //至少保证15个有效位
    const float million = 1.0e6;

    cout << "f = " << f << endl;
    cout << "f * million = " << million * f << endl;
    cout << "10 * f * million = " << 10*  million * f << endl;
    cout << "d * million = " << million * d << endl;
    return 0;
}
