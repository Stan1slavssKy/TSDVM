#include "stack.hpp"
#include <cassert>
#include <cstring>

//----------------------------------------------------------------------------------------------

stack::stack ():
capacity_(INIT_CAPACITY), size_(0)
{
    data_ = (double*) calloc (capacity_, sizeof (double));
    assert (data_);
}

stack::stack (double capacity, double size): 
capacity_ (capacity), size_ (size)
{
    data_ = (double*) calloc (capacity_, sizeof (double));
    assert (data_);
}

stack::stack (const stack& other):
capacity_ (other.capacity_), size_ (other.size_)
{
    data_ = (double*) realloc (data_, capacity_);
    assert (data_);
    memcpy (data_, other.data_, size_);

}

stack::stack (stack&& other):
capacity_(other.capacity_), size_(other.size_), data_(other.data_) 
{   
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

stack::~stack ()
{
    free (data_);
    size_ = 0;
    capacity_ = 0;
}

//----------------------------------------------------------------------------------------------

stack& stack::operator= (const stack& other) 
{
    if (this == &other) return *this;

    free (data_);
    
    size_ = other.size_;
    capacity_ = other.capacity_;

    data_ = (double*) calloc (capacity_, sizeof (double));
    assert (data_);
    
    memcpy (data_, other.data_, size_);
    
    return *this;
}

stack& stack::operator= (stack&& other)
{
    if (this == &other) return *this;

    free (data_);

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
    
    return *this;
}

//----------------------------------------------------------------------------------------------