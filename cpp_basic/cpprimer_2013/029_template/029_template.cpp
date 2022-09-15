#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

template <typename T>
int compare(const T& lhs, const T& rhs)
{
    if(lhs < rhs) return -1;
    if(rhs < lhs) return 1;
    return 0;
}

// Ex16.5
template <typename Arr>
void printArr(const Arr& arr)
{
    for(const auto &elem: arr)
        cout << elem << endl;
}

// Ex16.41
template<typename T>
auto sum(T lhs, T rhs) -> decltype( lhs + rhs)
{
    return lhs + rhs;
}

// Ex16.47
template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)  // preserves the constness and lvalue/rvalue property of its corresponding argument.
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));  // Using std::forward to Preserve Type Information in a Call
}

// print any type we don't otherwise handle
template <typename T> string debug_rep(const T &t)
{
    ostringstream ret; // see § 8.3 (p. 321)
    ret << t; // uses T's output operator to print a representation of t
    return ret.str(); // return a copy of the string to which ret is bound
}

// print pointers as their pointer value, followed by the object to which the pointer points
// NB: this function will not work properly with char*; see § 16.3 (p. 698)
template <typename T> string debug_rep(T *p)
{
    ostringstream ret;
    ret << "pointer: " << p; // print the pointer's own value
    if (p)
        ret << " " << debug_rep(*p); // print the value to which p points
    else
        ret << " null pointer"; // or indicate that the p is null
    return ret.str(); // return a copy of the string to which ret is bound
}

// print strings inside double quotes
string debug_rep(const string &s)
{
    return '"' + s + '"';
}

// convert the character pointers to string and call the string version of debug_rep
string debug_rep(char *p)
{
    return debug_rep(string(p));
}
string debug_rep(const char *p)
{
    return debug_rep(string(p));
}

/// variadic template
// function to end the recursion and print the last element
// this function must be declared before the variadic version of print is defined
template<typename T>
    ostream &print(ostream &os, const T &t)
{
    return os << t; // no separator after the last element in the pack
}
// this version of print will be called for all but the last element in the pack
template <typename T, typename... Args>
    ostream &print(ostream &os, const T &t, const Args&... rest)
{
    os << t << ", "; // print the first argument
    return print(os, rest...); // recursive call; print the other arguments
}

// call debug_rep on each argument in the call to print
template <typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
    // print(os, debug_rep(a1), debug_rep(a2), ..., debug_rep(an)
    return print(os, debug_rep(rest)...);
}

/// Template Specializations
// second version compare to handle string literals
template<size_t N, size_t M>
int compare(const char (&)[N], const char (&)[M]);


template <>
int compare(const char* const &p1, const char* const &p2);
// special version of compare to handle pointers to character arrays
// Specializations instantiate a template; they do not overload it.
template <>
int compare(const char* const &p1, const char* const &p2)
{
    return strcmp(p1, p2);
}

int main(int argc, char const *argv[])
{
    // Ex16.2.3
    // Test compare function
    // cout << compare(1, 0) << endl;
    // vector<int> vec1{ 1, 2, 3 }, vec2{ 4, 5, 6 };
    // cout << compare(vec1, vec2) << endl;

    //Ex16.5
    string s[] = {"1", "2", "3", "4"};
    // printArr(s);

    //Ex16.53
    int i = 1; double d = 2.0; 
    // print(cout, string("hello"), i, d, s[2], "\n");

    //Ex16.56
    // errorMsg(cerr, "fcnName", 343, "otherData", "other", "item");

    cout << compare("abc", "abcd") << endl;
    return 0;
}
