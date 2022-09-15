#ifndef BLOB_H
#define BLOB_H

#include <vector>
#include <memory>

// forward declarations needed for friend declarations in Blob
template <typename> class BlobPtr;
template <typename> class Blob;  // needed for parameters in operator==
// template <typename T>
//     bool operator==(const Blob<T>&, const Blob<T>&);

template <typename T> class Blob {
    // each instantiation of Blob grants access to the version of
    // BlobPtr and the equality operator instantiated with the same type
    friend class BlobPtr<T>;
    // friend bool operator==<T>
    //     (const Blob<T>&, const Blob<T>&);
public:
    typedef T value_type;
    typedef typename std::vector<T>::size_type size_type;
    // constructors
    Blob();
    Blob(std::initializer_list<T> il);
    template <typename It> Blob(It b, It e);  // member template of a class template
    // number of elements in the Blob
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // add and remove elements
    void push_back(const T &t) {data->push_back(t);}
    // move version; see § 13.6.3 (p. 548)
    void push_back(T &&t) { data->push_back(std::move(t)); }
    void pop_back();
    // element access
    T& front();
    T& back();
    const T& front() const;
    const T& back() const;
    T& operator[](size_type i); // defined in § 14.5 (p. 566)
    const T& operator[](size_type i) const;
private:
    std::shared_ptr<std::vector<T>> data;
    // throws msg if data[i] isn't valid
    void check(size_type i, const std::string &msg) const;
};


template <typename T>
bool operator ==(const BlobPtr<T>& lhs, const BlobPtr<T>& rhs);

template <typename T>
bool operator < (const BlobPtr<T>& lhs, const BlobPtr<T>& rhs);

// BlobPtr throws an exception on attempts to access a nonexistent element
template <typename T> class BlobPtr
{
    friend bool operator ==<T>
    (const BlobPtr<T>& lhs, const BlobPtr<T>& rhs);

    friend bool operator < <T>
    (const BlobPtr<T>& lhs, const BlobPtr<T>& rhs);
public:
    BlobPtr(): curr(0) { }
    BlobPtr(Blob<T> &a, size_t sz = 0):
        wptr(a.data), curr(sz) { }
    T& operator*() const
    { 
        auto p = check(curr, "dereference past end");
        return (*p)[curr]; // (*p) is the vector to which this object points
    }
    // increment and decrement
    BlobPtr& operator++(); // prefix operators
    BlobPtr operator++(int); // postfix operators
    BlobPtr& operator--();
    BlobPtr operator--(int);
private:
    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<T>>
    check(std::size_t, const std::string&) const;
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr; // current position within the array
};

template<typename T> bool operator==(const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
    if (lhs.wptr.lock() != rhs.wptr.lock()) {
		throw runtime_error("ptrs to different Blobs!");
	}
	return lhs.i == rhs.i;
}

template<typename T> bool operator< (const BlobPtr<T> &lhs, const BlobPtr<T> &rhs) {
	if (lhs.wptr.lock() != rhs.wptr.lock()) {
		throw runtime_error("ptrs to different Blobs!");
	}
	return lhs.i < rhs.i;
}

#endif
