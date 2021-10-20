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
    memcpy (data_, other.data_, capacity_ * sizeof (bool));
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
    for (size_t i = 0; i < capacity_; i++)
    {
        int buffer[8] = {0};
        unsigned char nmb = data_[i];
        unsigned char temp = 0;

        for (int i = 0; i < 8; i++)
        {
            temp = nmb;
            nmb = nmb % 2;
            buffer [7 - i] = nmb;
            nmb = temp / 2;
        }

        for (int i = 0; i < 8; i++)
            std::cout << buffer[i];

        std::cout << std::endl;
    }
}

void stack<bool>::expands_capacity ()
{
    capacity_ = capacity_ * STACK_INCREASE + 0.5;

    bool* temp = new bool[capacity_];
    assert (temp);

    memcpy(temp, data_, capacity_ * sizeof(bool));

    delete[] data_;
    data_ = temp;
}

void stack<bool>::push (bool value)
{
    if (size_ % 8 == 0 && size_ != 0)
    {
        expands_capacity ();
    }

    size_t nmb_occupied_bits_in_byte = size_;
    size_t occupied_bytes_counter = 0;

    if (size_ >= 8)
    {
        occupied_bytes_counter = size_ / 8;   
        nmb_occupied_bits_in_byte = size_ - 8 * occupied_bytes_counter;
    }

    value <<= (7 - nmb_occupied_bits_in_byte);

    data_[occupied_bytes_counter] |= value;

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