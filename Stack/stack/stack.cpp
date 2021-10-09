#include <iostream>
#include <cstring>
#include <cassert>

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

bool stack::operator==(const stack& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }
    if (capacity_ != other.capacity_)
    {
        return false;
    }
    if (memcmp(data_, other.data_, size_ * sizeof (double)))
    {
        return false;
    }
    return true;
}

bool stack::operator!=(const stack& other) const
{
    if (size_ != other.size_)
    {
        return true;
    }
    if (capacity_ != other.capacity_)
    {
        return true;
    }
    if (memcmp(data_, other.data_, size_ * sizeof (double)))
    {
        return true;
    }
    return false;
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
    if (!is_empty())
    {
        data_[--size_] = 0;
    }
}

void stack::print () const
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

bool stack::is_empty () const
{
    return size_ == 0;
}

double& stack::top () const
{
    if (is_empty())
    {
        std::cout << "stack is empty, cant return top" << std::endl;
        return data_[0];
    }
    else
    {
        return data_[size_ - 1];
    }
}

//----------------------------------------------------------------------------------------------