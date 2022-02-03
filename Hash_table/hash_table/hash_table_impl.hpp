#ifndef HASH_TABLE_HASH_TABLE_IMPL_HPP_INCLUDED
#define HASH_TABLE_HASH_TABLE_IMPL_HPP_INCLUDED

#include "../list/list_impl.hpp"
#include "hash_table.hpp"

#include <cstring>
#include <string>
#include <iostream>
#include <optional>

namespace s1ky {
template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table() : capacity_(default_size)
{
    keys_ = new List<key_t, data_t>[capacity_] {};
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table(size_t capacity) : capacity_(capacity)
{
    keys_ = new List<key_t, data_t>[capacity_] {};
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table(Hash_table<key_t, data_t>&& other) noexcept :
    capacity_(other.capacity_), size_(other.size_), keys_(other.keys_)
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

template<typename key_t, typename data_t>
unsigned int Hash_table<key_t, data_t>::hash_(key_t key) const                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
{
    return murmur_hash2(key) % capacity_;
}

template<typename key_t, typename data_t>
unsigned int Hash_table<key_t, data_t>::murmur_hash2(data_t key) const
{
    const unsigned int m    = 0x5bd1e995;
    const unsigned int seed = 0xbc9f1d34;
    const unsigned char* data = reinterpret_cast<const unsigned char*>(key);

    unsigned int len  = strlen(data);
    unsigned int hash = seed ^ len;
    unsigned int k    = 0;

    while (len >= 4)
    {
        k  = data[0];
        k |= data[1] << 8;
        k |= data[2] << 16;
        k |= data[3] << 24;

        k *= m;
        k ^= k >> 24;
        k *= m;

        hash *= m;
        hash ^= k;

        data += 4;
        len -= 4;
    }

    switch (len)
    {
        case 3:
            hash ^= data[2] << 16;

        case 2:
            hash ^= data[1] << 8;

        case 1:
            hash ^= data[0];
            hash *= m;
    };

    hash ^= hash >> 13;
    hash *= m;
    hash ^= hash >> 15;

    return hash;
}

//==================================================================================================================

template<typename key_t, typename data_t>
void Hash_table<key_t, data_t>::set_value(key_t key, data_t value)
{
    unsigned int idx = hash_(key);    

    List<key_t, data_t>* list_elem = keys_[idx].find_value(key);

    if (list_elem == nullptr)
    {
        keys_[idx].push(key, value);
    }

    ++size_;
}

template<typename key_t, typename data_t> 
std::optional<data_t> Hash_table<key_t, data_t>::get_value(key_t key) const
{
    unsigned int idx = hash_(key);    

    List<key_t, data_t>* list_elem = keys_[idx].find_value(key);

    if (list_elem != nullptr)
    {
        return list_elem->data_;;
    }
    
    return std::nullopt;
}

template<typename key_t, typename data_t>
void Hash_table<key_t, data_t>::remove(key_t key)
{   
    unsigned int idx = hash_(key);
    keys_[idx].delete_value_node(key);

    --size_;
}
}; // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_IMPL_HPP_INCLUDED