#ifndef HASPTR_H
#define HASPTR_H

#include <string>

// value-like
class HasPtr
{
    friend void swap(HasPtr &, HasPtr &);  // swap
private:
    std::string *ps;
    int i;
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) {}  // copy constructor
    HasPtr & operator=(const HasPtr &hp){  // assignment operator
        auto new_ps = new std::string(*hp.ps);
        delete ps;
        ps = new_ps;
        i = hp.i;
        return *this;
    }
    ~HasPtr(){  // destructor
        delete ps;
    }
};

inline void swap(HasPtr &hp1, HasPtr &hp2)
{
    using std::swap;
    swap(hp1.ps, hp2.ps);  // swap the pointers, not the string data
    swap(hp1.i, hp2.i);
}

// pointer-like reference count
class HasPtr1
{
private:
    std::string *ps;
    int i;
    std::size_t *use;  // member to keep track of how many objects share *ps
public:
    // constructor allocates a new string and a new counter, which it sets to 1
    HasPtr1(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    // copy constructor copies all three data members and increments the counter
    HasPtr1(const HasPtr1 &hp) : ps(hp.ps), i(hp.i), use(hp.use) {++*use;}  // copy constructor
    HasPtr1 & operator=(const HasPtr1 &hp){  // assignment operator
        ++*hp.use;  // increment the use count of the right-hand operand
        if(--*use == 0)  // then decrement this object's counter
        {
            delete ps;  // if no other users
            delete use;  // free this object's allocated members
        }
        ps = hp.ps;  // copy data from rhs into this object
        i = hp.i;
        use = hp.use;
        return *this;
    }
    ~HasPtr1(){  // destructor
        if(--*use == 0)
        {
            delete ps;
            delete use;
        }
    }
};

#endif