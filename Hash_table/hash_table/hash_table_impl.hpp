#ifndef HASH_TABLE_HASH_TABLE_IMPL_HPP
#define HASH_TABLE_HASH_TABLE_IMPL_HPP

#include "hash_table.hpp"
#include "../queue/queue_impl.hpp"

#include <iostream>
#include <string>

namespace s1ky
{
template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table() : size_(default_size)
{
    keys_ = new key_t[size_] {};
    for (int i = 0; i < size_; ++i)
    {
        list_queue::Queue<data_t>;
    }
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::~Hash_table()
{
    delete[] keys_;
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table(size_t size) : size_(size)
{
    keys_ = new key_t[size] {};
}


};     // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_IMPL_HPP