//overload function template(explicit specialization)
#include <iostream>

using namespace std;
//function template prototype
template <typename T>
void ShowArray(T arr[], int n);

template <typename T>
void ShowArray(T *arr[], int n);

struct debts
{
    char name[50];
    double amount;
};

int main()
{
    cout.precision(2);
    cout.setf(ios::fixed, ios::floatfield);

    int things[6] = {13, 31, 103, 301, 310, 130};
    struct debts mr_E[3] = {
        {"Ima Wolfe", 2400.0},
        {"Ura Foxe ", 1300.0},
        {"Iby Stout", 1900.0}
    };
    double *pd[3];
    //set pointers to the amount members of the structers in mr_E
    for (int i = 0; i < 3; i++)
        pd[i] = &mr_E[i].amount;
    cout << "Listing Mr. E's counts of things:\n";
    //things is an array of int
    ShowArray(things, 6); // use template A
    cout << "Listing Mr. E's debts: \n";
    //pd is an array of pointers to double
    ShowArray(pd, 3);
    return 0;
}

template <typename T>
void ShowArray(T arr[], int n)
{
    cout << "template A\n";

    for (int i = 0; i < n; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

template <typename T>
void ShowArray(T *arr[], int n)
{
    cout << "template B\n";

    for (int i = 0; i < n; i++)
        cout << *arr[i] << ' ';
    cout << endl;
}