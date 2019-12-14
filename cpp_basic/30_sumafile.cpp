#include <iostream>
#include <fstream> //file I/O
#include <cstdlib> //support for exit
using namespace std;

const int SIZE = 60;
int main(){
    char filename[SIZE];
    ifstream inFile; //oobject for handling file input

    cout << "Enter name of data file : ";
    cin.getline(filename,SIZE);
    inFile.open(filename); //open file
    if (!inFile.is_open()){ //检验
        cout << "Could not open the file " << filename << endl;
        cout << "Program terminating.\n";
        exit(EXIT_FAILURE);
    }
    double value;
    double sum = 0.0;
    int count = 0;

    inFile >> value; // get first value
    while (inFile.good()){ // 类型匹配 没有结束  
        ++count;
        sum += value;
        inFile >> value;
    }

    if (inFile.eof())
        cout << "end of file reached.\n";
    else if (inFile.fail())
        cout << "Input terminated by data mismatch.\n";
    else    
        cout << "Input terminated by unknown reason.\n";
    if (count == 0)
        cout << "No data processed.\n";
    else{
        cout << "Items read: " << count << endl;
        cout << "Sum : " << sum << endl;
        cout << "Average : " << sum / count << endl;
    }
    inFile.close();


    return 0;
}