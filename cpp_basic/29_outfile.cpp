#include <iostream>
#include <fstream> //file I/O
using namespace std;

int main(){
    char automobile[50];
    int year;
    double a_price;
    double d_price;

    ofstream outFile; //create object for output
    outFile.open("carinfo.txt"); // associate with a file

    cout << "Enter :";
    cin.getline(automobile,50);
    cout << "Enter year:" ;
    cin >> year;
    cout << "Enter price :";
    cin >> a_price;
    d_price = 0.913 * a_price;

    //display
    cout << fixed;
    cout.precision(2);
    cout.setf(ios_base::showpoint);
    cout << "Make and Model : " << automobile << endl;
    cout << "Year : " << year << endl;
    cout << " a_price : " << a_price << endl;
    cout << " d_price : " << d_price << endl;

    //file
    outFile << fixed;
    outFile.precision(2);
    outFile.setf(ios_base::showpoint);
    outFile << "Make and Model : " << automobile << endl;
    outFile << "Year : " << year << endl;
    outFile << " a_price : " << a_price << endl;
    outFile << " d_price : " << d_price << endl;

    outFile.close();




    return 0;
}