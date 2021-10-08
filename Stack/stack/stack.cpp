#include <cassert>
#include <cstring>
#include <iostream>

#include "stack.hpp"

//----------------------------------------------------------------------------------------------

stack::stack ():
    capacity_(init_capacity_), size_(0)
{
    data_ = new double[capacity_];
    assert (data_);
}

stack::stack (double* data, size_t size): 
    data_(data), size_ (size), capacity_(capacity_)
{
}

stack::stack (const stack& other):
    capacity_ (other.capacity_), size_ (other.size_)
{
    delete[] data_;
    new double[capacity_];

    assert (data_);
    memcpy (data_, other.data_, size_);

}

stack::stack (stack&& other):
    capacity_(other.capacity_), size_(other.size_), data_(other.data_) 
{   
    other.data_ = nullptr;
}

stack::~stack ()
{
    delete[] data_;
}

//----------------------------------------------------------------------------------------------

stack& stack::operator= (const stack& other) 
{
    if (this == &other) return *this;

    delete[] data_;
    
    size_ = other.size_;
    capacity_ = other.capacity_;

    data_ = new double[capacity_];
    assert (data_);
    
    memcpy(data_, other.data_, size_ * sizeof(double));
    
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
    
    return *this;
}

//----------------------------------------------------------------------------------------------

void stack::push (const double value)
{
    if (size_ == capacity_)
    {
        expands_capacity ();
    }
    
    data_[size_++] = value;
}

void stack::pop ()
{
    if (size_ != 0)
    {
        data_[--size_] = 0;
    }
}

void stack::print ()
{
    for (int i = 0; i < size_; i++)
    {
        std::cout << data_[i] << std::endl;
    }
}

void stack::expands_capacity ()
{
    capacity_ = capacity_ * stack_increase_;

    double* temp = new double[capacity_];
    assert (temp);

    memcpy(temp, data_, size_ * sizeof(double));

    delete[] data_;
    data_ = temp;
}

//----------------------------------------------------------------------------------------------