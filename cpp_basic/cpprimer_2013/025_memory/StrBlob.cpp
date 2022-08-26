#include "StrBlob.h"

StrBlob::StrBlob(): data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il):
    data(std::make_shared<std::vector<std::string>>(il)){}

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

std::string& StrBlob::front()
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string& StrBlob::back()
{
    check(0, "back on empty StrBlob");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
const std::string& StrBlob::front() const
{
    check(0, "front on empty StrBlob");
    return data->front();
}
const std::string& StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}

StrBlobPtr StrBlob::begin() {return StrBlobPtr(*this);}
StrBlobPtr StrBlob::end() {return StrBlobPtr(*this, data->size());}

std::shared_ptr<std::vector<std::string>>
    StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();  // is the vector still around?
    if (!ret)
        throw std::runtime_error("unbound StrBlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret; // otherwise, return a shared_ptr to the vector
}

std::string& StrBlobPtr::deref() const
{
    auto p = check(curr, "dereference past end");
    return (*p)[curr]; // (*p) is the vector to which this object points
}

StrBlobPtr& StrBlobPtr::incr() // prefix version
{
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of StrBlobPtr");
    ++curr;
    return *this;
}