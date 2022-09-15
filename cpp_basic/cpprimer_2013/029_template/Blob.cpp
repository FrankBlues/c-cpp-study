#include "Blob.h"
template <typename T>
Blob<T>::Blob(): data(std::make_shared<std::vector<T>>()){}
template <typename T>
Blob<T>::Blob(std::initializer_list<T> il):
    data(std::make_shared<std::vector<T>>(il)){}
template <typename T>
template <typename It> 
Blob<T>::Blob(It b, It e):
    data(std::make_shared<std::vector<T>>(b, e)){}

template <typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}

template <typename T>
T& Blob<T>::front()
{
    // if the vector is empty, check will throw
    check(0, "front on empty Blob");
    return data->front();
}
template <typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}
template <typename T>
T& Blob<T>::operator[](size_type i)
{
    // if i is too big, check will throw, preventing access to a nonexistent element
    check(i, "subscript out of range");
    return (*data)[i];
}
template <typename T>
const T& Blob<T>::operator[](size_type i) const
{
    // if i is too big, check will throw, preventing access to a nonexistent element
    check(i, "subscript out of range");
    return (*data)[i];
}
template <typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}
template <typename T>
const T& Blob<T>::front() const
{
    check(0, "front on empty Blob");
    return data->front();
}
template <typename T>
const T& Blob<T>::back() const
{
    check(0, "back on empty Blob");
    return data->back();
}

template <typename T>
std::shared_ptr<std::vector<T>>
    BlobPtr<T>::check(std::size_t i, const std::string &msg) const
{
    auto ret = wptr.lock();  // is the vector still around?
    if (!ret)
        throw std::runtime_error("unbound BlobPtr");
    if (i >= ret->size())
        throw std::out_of_range(msg);
    return ret; // otherwise, return a shared_ptr to the vector
}


// postfix: increment/decrement the object but return the unchanged value
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++()
{
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of BlobPtr");
    ++curr;
    return *this;
}

// postfix: increment/decrement the object but return the unchanged value
template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int)
{
    // no check needed here; the call to prefix increment will do the check
    BlobPtr ret = *this; // save the current value
    ++*this; // advance one element; prefix ++ checks the increment
    return ret; // return the saved state
}

// postfix: increment/decrement the object but return the unchanged value
template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
    --curr;
    check(curr, "decrement past begin of BlobPtr");
    return *this;
}

// postfix: increment/decrement the object but return the unchanged value
template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int)
{
    // no check needed here; the call to prefix increment will do the check
    BlobPtr ret = *this; // save the current value
    --*this; // advance one element; prefix ++ checks the increment
    return ret; // return the saved state
}