#ifndef STRBLOB_H
#define STRBLOB_H

#include <vector>
#include <memory>

class StrBlobPtr;

class StrBlob {
public:
    friend class StrBlobPtr;
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // add and remove elements
    void push_back(const std::string &t) {data->push_back(t);}
    void pop_back();
    // element access
    std::string& front();
    std::string& back();
    const std::string& front() const;
    const std::string& back() const;
    StrBlobPtr begin();
    StrBlobPtr end();
    ~StrBlob(){}

private:
    std::shared_ptr<std::vector<std::string>> data;
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};


class StrBlobPtr
{
private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<std::string>>
        check(std::size_t, const std::string&) const;
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr; // current position within the array
public:
    StrBlobPtr(): curr(0){}
    StrBlobPtr(StrBlob &a, std::size_t sz = 0):wptr(a.data), curr(sz){}
    std::string& deref() const;
    StrBlobPtr& incr(); // prefix version
    // increment and decrement
    StrBlobPtr& operator++(); // prefix operators
    StrBlobPtr& operator--();
    StrBlobPtr operator++(int); // postfix operators
    StrBlobPtr operator--(int);
    std::string& operator*() const
    { 
        auto p = check(curr, "dereference past end");
        return (*p)[curr]; // (*p) is the vector to which this object points
    }
    std::string* operator->() const
    { 
        // delegate the real work to the dereference operator
        return & this->operator*();
    }

    ~StrBlobPtr(){}
};



#endif
