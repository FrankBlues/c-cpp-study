#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

struct Person
{
    std::string name;
    std::string address;
    std::string getName() const {return name;}  // const修饰隐含的this
    std::string getAddress() const {return address;}
};
std::istream &read(std::istream&, Person&);
std::ostream &print(std::ostream&, const Person&);

std::istream &read(std::istream &is, Person &p)
{
    is >> p.name >> p.address;
    return is;
}

std::ostream &print(std::ostream &os, const Person &p)
{
    os << p.name << " " << p.address;
    return os;
}

#endif