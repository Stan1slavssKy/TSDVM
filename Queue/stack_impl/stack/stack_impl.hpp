#ifndef STACK_STACK_IMPL_HPP_INCLUDED
#define STACK_STACK_IMPL_HPP_INCLUDED

#include "stack.hpp"

#include <cassert>
#include <cstring>
#include <iostream>

namespace s1ky {

template<typename T>
Stack<T>::Stack() : capacity_(INIT_CAPACITY)
{
    data_ = new T[capacity_] {};
    assert(data_);
}

template<typename T>
Stack<T>::Stack(T* data, size_t size) : capacity_(size + INIT_CAPACITY), size_(size)
{
    data_ = new T[capacity_] {};
    assert(data_);

    memcpy(data_, data, size_ * sizeof(T));
}

template<typename T>
Stack<T>::Stack(const Stack& other) : capacity_(other.capacity_), size_(other.size_)
{
    data_ = new T[capacity_] {};

    assert(data_);
    memcpy(data_, other.data_, size_ * sizeof(T));
}

template<typename T>
Stack<T>::Stack(Stack&& other) noexcept : capacity_(other.capacity_), size_(other.size_), data_(other.data_)
{
    other.data_ = nullptr;
}

template<typename T>
Stack<T>::~Stack()
{
    delete[] data_;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& other)
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
Stack<T>& Stack<T>::operator=(Stack&& other) noexcept
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
bool Stack<T>::operator==(const Stack& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }
    if (capacity_ != other.capacity_)
    {
        return false;
    }
    if (memcmp(data_, other.data_, size_ * sizeof(T)) != 0)
    {
        return false;
    }

    return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack& other) const
{
    if (size_ != other.size_)
    {
        return true;
    }
    if (capacity_ != other.capacity_)
    {
        return true;
    }
    if (memcmp(data_, other.data_, size_ * sizeof(T)) != 0)
    {
        return true;
    }
    return false;
}

template<typename T>
void Stack<T>::push(T value)
{
    if (size_ == capacity_)
    {
        expands_capacity();
    }

    data_[size_++] = value;
}

template<typename T>
void Stack<T>::pop()
{
    if (!is_empty())
    {
        data_[--size_] = 0;
    }
}

template<typename T>
void Stack<T>::print() const
{
    for (size_t i = 0; i < size_; i++) { std::cout << data_[i] << std::endl; }
}

template<typename T>
void Stack<T>::expands_capacity()
{
    capacity_ = static_cast<size_t>(static_cast<double>(capacity_) * STACK_INCREASE);

    T* temp = new T[capacity_] {};
    assert(temp);

    memcpy(temp, data_, size_ * sizeof(T));

    delete[] data_;
    data_ = temp;
}

template<typename T>
bool Stack<T>::is_empty() const
{
    return size_ == 0;
}

template<typename T>
T& Stack<T>::top()
{
    if (is_empty())
    {
        std::cout << "Stack is empty, cant return top" << std::endl;
        return data_[0];
    }

    return data_[size_ - 1];
}

template<typename T>
const T& Stack<T>::top() const
{
    if (is_empty())
    {
        std::cout << "Stack is empty, cant return top" << std::endl;
        return data_[0];
    }

    return data_[size_ - 1];
}

template<typename T>
size_t Stack<T>::size() const
{
    return size_;
}

} // namespace s1ky

#endif // STACK_STACK_IMPL_HPP_INCLUDED