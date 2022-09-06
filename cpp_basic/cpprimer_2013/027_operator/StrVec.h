#ifndef STRVEC_H
#define STRVEC_H

#include <string>
#include <algorithm>
#include <memory>


// simplified implementation of the memory allocation strategy for a vector-like class
class StrVec {
public:
    StrVec(): // the allocator member is default initialized
        elements(nullptr), first_free(nullptr), cap(nullptr) {
    }
    StrVec(std::initializer_list<std::string>);
    StrVec(const StrVec&); // copy constructor
    StrVec &operator=(const StrVec&); // copy assignment
    StrVec(StrVec &&) noexcept; // move won't throw any exceptions
    StrVec &operator=(StrVec&) noexcept;
    ~StrVec(); // destructor
    StrVec &operator=(std::initializer_list<std::string>);  // saaignment overwrite
    std::string& operator[](std::size_t n)  // subscript overwrite
    { return elements[n]; }
    const std::string& operator[](std::size_t n) const  // subscript overwrite const version
    { return elements[n]; }
    void push_back(const std::string&); // copy the element
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }

    void reserve(size_t new_cap);
    void resize(size_t count);
    void resize(size_t count, const std::string&);
    // ...
private:
    std::allocator<std::string> alloc; // allocates the elements
    // used by the functions that add elements to the StrVec
    void chk_n_alloc()
        { if (size() == capacity()) reallocate(); }
    // utilities used by the copy constructor, assignment operator, and destructor
    std::pair<std::string*, std::string*> alloc_n_copy
        (const std::string*, const std::string*);
    void free(); // destroy the elements and free the space
    void reallocate(); // get more space and copy the existing elements
    std::string *elements; // pointer to the first element in the array
    std::string *first_free; // pointer to the first free element in the array
    std::string *cap; // pointer to one past the end of the array
};

#endif