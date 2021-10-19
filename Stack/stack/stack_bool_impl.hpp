#ifndef STACK_STACK_BOOL_IMPL_HPP
#define STACK_STACK_BOOL_IMPL_HPP

#include <iostream>
#include <cstring>
#include <cassert>

#include "stack_impl.hpp"

namespace s1ky
{

template <>
class stack<bool>
{
    public:
        stack ();
        stack (bool* data, size_t size);
        stack (const stack& other);
        stack (stack&& other);

        ~stack ();

        stack& operator= (const stack& other);
        stack& operator= (stack&& other);
        
        bool operator==(const stack& other) const;
        bool operator!=(const stack& other) const;

        void push (bool value);
        void pop ();
        void print () const;
        bool is_empty () const;
        
        bool& top (); 
        const bool& top () const; 
        size_t size () const;

        const size_t INIT_CAPACITY  = 2;
        const double STACK_INCREASE = 1.5;

    private:
        size_t capacity_;
        size_t size_;
        bool* data_;
                    
        void expands_capacity ();
};

stack<bool>::stack ():
    capacity_(INIT_CAPACITY), size_(0)
{
    data_ = new bool[capacity_];
    assert (data_);
}

stack<bool>::stack (bool* data, size_t size): 
    data_(data), size_ (size), capacity_(capacity_)
{
    bool* temp = new bool[capacity_];
    assert (temp);

    memcpy (temp, data_, size_ * sizeof(bool));
    data_ = temp;   
}

stack<bool>::stack (const stack& other):
    capacity_ (other.capacity_), size_ (other.size_)
{
    new bool[capacity_];

    assert (data_);
    memcpy (data_, other.data_, size_);
}

stack<bool>::stack (stack&& other):
    capacity_(other.capacity_), size_(other.size_), data_(other.data_) 
{   
    other.data_ = nullptr;
}

stack<bool>::~stack ()
{
    delete[] data_;
}

void stack<bool>::print () const
{
    for (int i = 0; i < size_; i++)
    {
        if (data_[i] == 1)
        {
            std::cout << "true" << std::endl;
        }
        else 
        {
            std::cout << "false" << std::endl;
        }
    }
}

void stack<bool>::expands_capacity ()
{
    capacity_++;

    bool* temp = new bool[capacity_];
    assert (temp);

    memcpy(temp, data_, size_);

    delete[] data_;
    data_ = temp;
}

void stack<bool>::push (bool value)
{
    if (size_ == 8 * capacity_)
    {
        expands_capacity ();
    }

    size_t x = size_;

    if (size_ >= 8)
    {
        size_t x = size_ / 8;   
    }

    value << (8 - size_);
    data_[0] | value;

    if (size_ % 8 == 0)
    {
        //bytes_counter++;
    }

    size_++;
}

void stack<bool>::pop ()
{
    if (!is_empty())
    {
        data_[--size_] = 0;
    }
}

bool stack<bool>::is_empty () const
{
    return size_ == 0;
}


}//namespace s1ky

#endif //STACK_STACK_BOOL_IMPL_HPP