#ifndef QUEUE_IMPL_HPP
#define QUEUE_IMPL_HPP

#include "queue.hpp"

#include <iostream>
#include <cassert>
#include <cstring>

namespace s1ky 
{
template<typename T>
queue<T>::queue() : capacity_(INIT_CAPACITY), size_(0)
{
    data_ = new T[capacity_] {};
    assert(data_);
}

template<typename T>
queue<T>::queue(const queue& other) : capacity_(other.capacity_), size_(other.size_)
{
    assert(other.data_);
    
    data_ = new T[size_] {};
    assert(data_);

    memcpy(data_, other.data_, size_ * sizeof(T));
}

template<typename T>
queue<T>::queue(queue&& other) : capacity_(other.capacity_), size_(other.size_), data_(other.data_)
{
    assert(data_);
    other.data_ = nullptr;
}

template<typename T>
queue<T>::~queue()
{
    assert(data_);
    delete[] data_;
}

template<typename T>
queue<T>& queue<T>::operator=(queue&& other)
{
    if (this == &other) return *this;

    delete[] data_;

    capacity_   = other.capacity_;
    size_       = other.size_;
    data_       = other.data_;

    other.data_ = nullptr;

    return *this;
}

} //namespace s1ky

#endif //QUEUE_IMPL_HPP
