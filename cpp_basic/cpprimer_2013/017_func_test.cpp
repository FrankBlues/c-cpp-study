#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cstring>
using namespace std;
// #include "test.h"

unsigned call_me()
{
    static unsigned times = 0;
    return times++;
}

void swap(int *p, int *q)
{
    int temp = *q;
    *q = *p;
    *p = temp;
}

void swap(int &p, int &q)
{
    int temp = q;
    q = p;
    p = temp;
}

void reset(int &i)
{
    i = 0;
}

string::size_type find_char(const string &s, char c,
string::size_type &occurs)
{
    auto ret = s.size(); // position of the first occurrence, if any
    occurs = 0; // set the occurrence count parameter
    for (decltype(ret) i = 0; i != s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size())
            ret = i; // remember the first occurrence of c
            ++occurs; // increment the occurrence count
        }
    }
    return ret; // count is returned implicitly in occurs
}

bool has_capital(const string &s)
{
    for (auto &c : s)
    {
        if (isupper(c))
            return true;
    }
    return false;
}

void to_lower(string &s)
{
    for (auto &c : s)
    {
        if (isupper(c))
            c = tolower(c);
    }
}

int sum(vector<int>::const_iterator i1, vector<int>::const_iterator i2, int i)
{
    return *i1 + *i2 + i;
}

void print(const int cp[4])
{
    if (cp)
    {
        while (*cp)
        {
            cout << *cp++;
        }
        
    }

}
// void print(const int*);
// void print(const int[]); // shows the intent that the function takes an
// void print(const int[10]);
void print(const int *beg, const int *end)
{
    while (beg != end)
        cout << *beg++ << endl;
}

void print(const int a[], size_t size)
{
    for (size_t i = 0; i != size; ++i)
        cout << a[i] << endl;
}

int params_sum(initializer_list<int> params)
{
    int sum = 0;
    for(auto &i: params)
        sum += i;
    return sum;
}

// bool str_subrange(const string &str1, const string &str2)
// {
//     // same sizes: return normal equality test
//     if (str1.size() == str2.size())
//         return str1 == str2; // ok: == returns bool
//     // find the size of the smaller string; conditional operator, see § 4.7 (p. 151)
//     auto size = (str1.size() < str2.size()) ? str1.size() : str2.size();
//     // look at each element up to the size of the smaller string
//     for (decltype(size) i = 0; i != size; ++i) {
//         if (str1[i] != str2[i])
//         return; // error #1: no return value; compiler should detect this error
//     }
//     // error #2: control might flow off the end of the function without a return
//     // the compiler might not detect this error
// }
int &get(int *arry, int index) { return arry[index]; }

void print(const std::vector<int> &ivec, std::vector<int>::const_iterator it) {
    if (it == ivec.end())
        return;
    std::cout << *it++ << std::endl;
    print(ivec, it);
    #ifndef NDEBUG  // If NDEBUG is defined, the code is ignored
    cout << ivec.size() << endl;
    #endif
}

string (&func())[10];
typedef string sa[0];
sa &func1();
auto func2() -> string(&)[10];

int *reset(int *);
double *reset(double *);
int calc(int&, int&);
int calc(const int&, const int&);

int f(const int&, const int&);

int (*f1(const int&, const int&));
typedef int(*f2)(const int&, const int&);
using f3 = int(*)(const int&, const int&);

int add(const int&a, const int&b)
{
    return a + b;
}

int subtract(const int&a, const int&b)
{
    return a - b;
}

int multiply(const int&a, const int&b)
{
    return a * b;
}

int divide(const int&a, const int&b)
{
    return a / b;
}


int main(int argc, char *argv[])
{
    vector<int> v{
        5, 7, 77, 23, 10, 81
    };

    int a = 9, b = 3;
    vector<decltype(f) *> pf = {add, subtract, multiply, divide};

    for (auto &v: pf)
        cout << v(a, b) << endl;

    return 0;
}