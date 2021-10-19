#ifndef STACK_STACK_BOOL_IMPL_HPP
#define STACK_STACK_BOOL_IMPL_HPP

//===========================================================================================

#include <iostream>
#include <cstring>
#include <cassert>

//===========================================================================================

namespace s1ky
{

template <> void stack<bool>::print () const
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

template <> void stack<bool>::expands_capacity ()
{
    capacity_++;

    bool* temp = new bool[capacity_];
    assert (temp);

    memcpy(temp, data_, size_);

    delete[] data_;
    data_ = temp;
}

template <> void stack<bool>::push (const bool value)
{
    if (size_ == 8 * capacity_)
    {
        expands_capacity ();
    }

    value << (8 - size_);
    data_[0] | value;

    if (size_ % 8 == 0)
    {
        bytes_counter++;
    }

    size_++;
}

template <> void stack<bool>::pop ()
{
    if (!is_empty())
    {
        data_[--size_] = 0;
    }
}



}//namespace s1ky

//===========================================================================================

#endif //STACK_STACK_BOOL_IMPL_HPP