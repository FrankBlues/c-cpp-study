#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>

class Person
{
    friend std::istream &read(std::istream&, Person&);  // can access private members
    friend std::ostream &print(std::ostream&, const Person&);
    private:
        std::string name;
        std::string address;
        unsigned age = 1;
    public:
        Person() = default; // 默认
        Person(const std::string &name, const std::string &address, const int &age): name(name), address(address), age(age) {}
        Person(const std::string &name, const std::string &address): Person(name, address, 2) {}
        explicit Person(const std::string &name): name(name) {}
        explicit Person(std::istream &);

        std::string getName() const {return name;}  // const修饰隐含的this
        std::string getAddress() const {return address;}
};


std::istream &read(std::istream&, Person&);
std::ostream &print(std::ostream&, const Person&);

Person::Person(std::istream &is)
{
    read(is, *this);
}

std::istream &read(std::istream &is, Person &p)
{
    is >> p.name >> p.address;
    return is;
}

std::ostream &print(std::ostream &os, const Person &p)
{
    os << "Name: " << p.name << "  Address: " << p.address << " Age: " << p.age;
    return os;
}

#endif