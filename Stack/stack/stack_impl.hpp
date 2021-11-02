#ifndef STACK_STACK_IMPL_HPP_INCLUDED
#define STACK_STACK_IMPL_HPP_INCLUDED

#include "stack.hpp"

#include <cassert>
#include <cstring>
#include <iostream>

namespace s1ky {

template<typename T>
stack<T>::stack() : capacity_(INIT_CAPACITY), size_(0)
{
    data_ = new T[capacity_] {};
    assert(data_);
}

template<typename T>
stack<T>::stack(T* data, size_t size) : capacity_(size + INIT_CAPACITY), size_(size)
{
    data_ = new T[capacity_] {};
    assert(data_);

    memcpy(data_, data, size_ * sizeof(T));
}

template<typename T>
stack<T>::stack(const stack& other) : capacity_(other.capacity_), size_(other.size_)
{
    data_ = new T[capacity_] {};

    assert(data_);
    memcpy(data_, other.data_, size_ * sizeof(T));
}

template<typename T>
stack<T>::stack(stack&& other) : capacity_(other.capacity_), size_(other.size_), data_(other.data_)
{
    other.data_ = nullptr;
}

template<typename T>
stack<T>::~stack()
{
    delete[] data_;
}

template<typename T>
stack<T>& stack<T>::operator=(const stack& other)
{
    if (this == &other)
        return *this;

    delete[] data_;

    size_     = other.size_;
    capacity_ = other.capacity_;

    data_ = new T[capacity_] {};
    assert(data_);

    memcpy(data_, other.data_, size_ * sizeof(T));

    return *this;
}

template<typename T>
stack<T>& stack<T>::operator=(stack&& other)
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

template<typename T>
bool stack<T>::operator==(const stack& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }
    if (capacity_ != other.capacity_)
    {
        return false;
    }
    if (memcmp(data_, other.data_, size_ * sizeof(T)))
    {
        return false;
    }
    return true;
}

template<typename T>
bool stack<T>::operator!=(const stack& other) const
{
    if (size_ != other.size_)
    {
        return true;
    }
    if (capacity_ != other.capacity_)
    {
        return true;
    }
    if (memcmp(data_, other.data_, size_ * sizeof(T)))
    {
        return true;
    }
    return false;
}

template<typename T>
void stack<T>::push(T value)
{
    if (size_ == capacity_)
    {
        expands_capacity();
    }

    data_[size_++] = value;
}

template<typename T>
void stack<T>::pop()
{
    if (!is_empty())
    {
        data_[--size_] = 0;
    }
}

template<typename T>
void stack<T>::print() const
{
    for (int i = 0; i < size_; i++) { std::cout << data_[i] << std::endl; }
}

template<typename T>
void stack<T>::expands_capacity()
{
    capacity_ = capacity_ * STACK_INCREASE;

    T* temp = new T[capacity_] {};
    assert(temp);

    memcpy(temp, data_, size_ * sizeof(T));

    delete[] data_;
    data_ = temp;
}

template<typename T>
bool stack<T>::is_empty() const
{
    return size_ == 0;
}

template<typename T>
T& stack<T>::top()
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

template<typename T>
const T& stack<T>::top() const
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

template<typename T>
size_t stack<T>::size() const
{
    return size_;
}

} // namespace s1ky

#endif // STACK_STACK_IMPL_HPP_INCLUDED