#include <iostream>
#include <type_traits>
#include <typeinfo>
#ifndef _MSC_VER
#include <cxxabi.h>
#endif
#include <memory>
#include <string>
#include <cstdlib>

template <class T>
std::string
type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::unique_ptr<char, void (*)(void *)> own(
#ifndef _MSC_VER
        abi::__cxa_demangle(typeid(TR).name(), nullptr,
                            nullptr, nullptr),
#else
        nullptr,
#endif
        std::free);
    std::string r = own != nullptr ? own.get() : typeid(TR).name();
    if (std::is_const<TR>::value)
        r += " const";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}
int main()
{
    int i = 0, &r = i;
    auto a = r; // int

    const int ci = i, &cr = ci;
    auto b = ci; // int
    auto c = cr; // int
    auto d = &i; // int *
    auto e = &ci; // const int * 底层const 
    const auto f = ci; // const int 顶层const 

    auto &g = ci; //const int
    const auto &h = ci; // const &

    auto *p = &ci; // const int *
    const auto j2 = ci, &k2 = ci; // j2: const int,  k2: const int &

    std::cout << "type of a: " << type_name<decltype(a)>() << '\n'
              << "type of b: " << type_name<decltype(b)>() << '\n'
              << "type of c: " << type_name<decltype(c)>() << '\n'
              << "type of d: " << type_name<decltype(d)>() << '\n'
              << "type of e: " << type_name<decltype(e)>() << '\n'
              << "type of f: " << type_name<decltype(f)>() << '\n'
              << "type of g: " << type_name<decltype(g)>() << '\n'
              << "type of h: " << type_name<decltype(h)>() << '\n'
              << "type of p: " << type_name<decltype(p)>() << '\n'
              << "type of j2: " << type_name<decltype(j2)>() << '\n'
              << "type of k2: " << type_name<decltype(k2)>() << '\n'
              
              ;
    // std::cout << r2 << "  " << d << std::endl;
    return 0;
}
