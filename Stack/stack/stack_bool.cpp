#include "stack_impl.hpp"

#include <cassert>
#include <climits>
#include <cstring>
#include <iostream>

namespace s1ky {

stack<bool>::stack() : capacity_(INIT_CAPACITY), size_(0)
{
    data_ = new unsigned char[capacity_] {};
    assert(data_);
}

stack<bool>::stack(unsigned char* data, size_t size) : capacity_(size + INIT_CAPACITY), size_(size)
{
    data_ = new unsigned char[capacity_] {};
    assert(data_);

    memcpy(data_, data, size_ * sizeof(unsigned char));
}

stack<bool>::stack(const stack& other) : capacity_(other.capacity_), size_(other.size_)
{
    data_ = new unsigned char[capacity_] {};

    assert(data_);
    memcpy(data_, other.data_, capacity_ * sizeof(unsigned char));
}

stack<bool>::stack(stack&& other) : capacity_(other.capacity_), size_(other.size_), data_(other.data_)
{
    other.data_ = nullptr;
}

stack<bool>::~stack()
{
    delete[] data_;
}

stack<bool>& stack<bool>::operator=(const stack& other)
{
    if (this == &other)
        return *this;

    size_     = other.size_;
    capacity_ = other.capacity_;

    delete[] data_;
    data_ = new unsigned char[capacity_] {};
    assert(data_);

    memcpy(data_, other.data_, (size_ / 8 + 1) * sizeof(unsigned char));

    return *this;
}

stack<bool>& stack<bool>::operator=(stack&& other)
{
    if (this == &other)
        return *this;

    delete[] data_;

    data_     = other.data_;
    size_     = other.size_;
    capacity_ = other.capacity_;

    other.data_ = nullptr;

    return *this;
}

bool stack<bool>::operator==(const stack& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }
    if (capacity_ != other.capacity_)
    {
        return false;
    }
    if (memcmp(data_, other.data_, (size_ / 8 + 1) * sizeof(unsigned char)))
    {
        return false;
    }
    return true;
}

bool stack<bool>::operator!=(const stack& other) const
{
    if (size_ != other.size_)
    {
        return true;
    }
    if (capacity_ != other.capacity_)
    {
        return true;
    }
    if (memcmp(data_, other.data_, (size_ / 8 + 1) * sizeof(unsigned char)))
    {
        return true;
    }
    return false;
}

void stack<bool>::print() const
{
    size_t nmb_occupied_bytes = size_ / 8 + 1;

    for (size_t idx = 0; idx < nmb_occupied_bytes; idx++)
    {
        unsigned char buffer[8] = {};
        unsigned char nmb       = data_[idx];
        unsigned char temp      = 0;

        for (size_t idx_1 = 0; idx_1 < 8; idx_1++)
        {
            temp              = nmb;
            temp              = temp % 2;
            buffer[7 - idx_1] = temp;
            nmb               = nmb / 2;
        }

        for (size_t idx_2 = 0; idx_2 < 8; idx_2++) std::cout << static_cast<int>(buffer[idx_2]);

        std::cout << std::endl;
    }
}

void stack<bool>::expands_capacity()
{
    capacity_ = capacity_ * STACK_INCREASE;

    unsigned char* temp = new unsigned char[capacity_] {};
    assert(temp);

    size_t len_copied_data = size_ / 8;

    for (size_t i = 0; i < len_copied_data; i++)
    {
        if (capacity_ < len_copied_data)
        {
            std::cout << "Error" << std::endl;
            break;
        }
        temp[i] = data_[i];
    }

    delete[] data_;
    data_ = temp;
}

void stack<bool>::push(bool bool_value)
{
    unsigned char value = bool_value;

    if (size_ / 8 == capacity_)
    {
        expands_capacity();
    }

    size_t nmb_occupied_bits_in_byte = size_;
    size_t occupied_bytes_counter    = 0;

    if (size_ >= 8)
    {
        occupied_bytes_counter    = size_ / CHAR_BIT;
        nmb_occupied_bits_in_byte = size_ % CHAR_BIT;
    }

    value <<= (CHAR_BIT - 1 - nmb_occupied_bits_in_byte);
    data_[occupied_bytes_counter] |= value;

    size_++;
}

void stack<bool>::pop()
{
    if (!is_empty())
    {
        size_t nmb_occupied_bits_in_byte = size_;
        size_t occupied_bytes_counter    = 0;

        if (size_ >= 8)
        {
            occupied_bytes_counter    = size_ / CHAR_BIT;
            nmb_occupied_bits_in_byte = size_ % CHAR_BIT;
        }

        unsigned char value = UCHAR_MAX - 1; // in binary 11111110

        if (nmb_occupied_bits_in_byte != 0)
        {
            value <<= (CHAR_BIT - nmb_occupied_bits_in_byte);
            data_[occupied_bytes_counter] &= value;
        }
        else
        {
            data_[occupied_bytes_counter - 1] &= value;
        }

        size_--;
    }
    else
    {
        std::cout << "Cant push, size = 0" << std::endl;
    }
}

bool stack<bool>::is_empty() const
{
    return size_ == 0;
}

size_t stack<bool>::size() const
{
    return size_;
}

bool stack<bool>::top() const
{
    if (!is_empty())
    {
        size_t nmb_occupied_bits_in_byte = size_;
        size_t occupied_bytes_counter    = 0;

        if (size_ >= 8)
        {
            occupied_bytes_counter    = size_ / CHAR_BIT;
            nmb_occupied_bits_in_byte = size_ % CHAR_BIT;
        }

        unsigned char cur_data = 0;
        unsigned char value    = 1; // in binary 00000001
        bool          out_nmb  = false;

        if (nmb_occupied_bits_in_byte != 0)
        {
            cur_data = data_[occupied_bytes_counter];
            value <<= (CHAR_BIT - nmb_occupied_bits_in_byte);
            out_nmb = (cur_data &= value);
        }
        else
        {
            cur_data = data_[occupied_bytes_counter - 1];
            out_nmb  = (cur_data &= value);
        }

        return out_nmb;
    }
    else
    {
        std::cout << "Cant return top of the stack, stack is empty" << std::endl;
        return 0;
    }
}

} // namespace s1ky