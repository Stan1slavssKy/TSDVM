#ifndef HASH_TABLE_HASH_TABLE_IMPL_HPP
#define HASH_TABLE_HASH_TABLE_IMPL_HPP

#include "hash_table.hpp"
#include "../queue/queue_impl.hpp"

#include <iostream>
#include <string>
#include <cstring>

namespace s1ky
{
template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table() : size_(default_size)
{
    keys_ = new key_t[size_] {};
    for (int i = 0; i < size_; ++i)
    {
        list_queue::Queue<data_t> qu;
        keys_[i] = qu.front();
    }
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table(size_t size, data_t init_val) : size_(size)
{
    keys_ = new key_t[size] {};
    for (int i = 0; i < size_; ++i)
    {
        list_queue::Queue<data_t> qu(init_val);
        keys_[i] = qu.front();
    }
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table(const Hash_table<key_t, data_t>& other) : size_(other.size_)
{
    memcpy(keys_, other.keys_, size_);
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table(Hash_table<key_t, data_t>&& other) noexcept : size_(other.size_), keys_(other.keys_)
{
    other.keys_ = nullptr;
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::~Hash_table()
{
    delete[] keys_;
}

//==================================================================================================================

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>& Hash_table<key_t, data_t>::operator=(const Hash_table<key_t, data_t>& other)
{
    if (this == &other)
    {
        return *this;
    }

    size_ = other.size_;

    memcpy(keys_, other.keys_, size_);

    return *this;
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>& Hash_table<key_t, data_t>::operator=(Hash_table<key_t, data_t>&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    size_ = other.size_;
    keys_ = other.keys_;

    other.keys_ = nullptr;

    return *this;
}

//==================================================================================================================


};     // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_IMPL_HPP