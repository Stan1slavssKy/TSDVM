#ifndef HASH_TABLE_HASH_TABLE_HASH_TABLE_IMPL_HPP_INCLUDED_
#define HASH_TABLE_HASH_TABLE_HASH_TABLE_IMPL_HPP_INCLUDED_

#include "../list/list_impl.hpp"
#include "hash_table.hpp"

#include <cstring>
#include <iostream>
#include <optional>
#include <string>
#include <typeinfo>

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

    delete[] keys_;

    size_ = other.size_;
    keys_ = other.keys_;

    other.keys_ = nullptr;

    return *this;
}

//==================================================================================================================

template<typename key_t, typename data_t>
size_t Hash_table<key_t, data_t>::hash_(key_t& key) const
{
    return murmur_hash2(key) % capacity_;
}

template<typename key_t, typename data_t>
size_t Hash_table<key_t, data_t>::murmur_hash2(key_t& key)
{
    const size_t m    = 0x5bd1e995;
    const size_t seed = 0xbc9f1d34;

    const unsigned char* data = reinterpret_cast<const unsigned char*>(key);

    size_t len  = strlen(reinterpret_cast<const char*>(key));
    size_t hash = seed ^ len;
    size_t k    = 0;

    while (len >= 4)
    {
        k = data[0];
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
    case 3: hash ^= data[2] << 16; break;

    case 2: hash ^= data[1] << 8; break;

    case 1:
        hash ^= data[0];
        hash *= m;
        break;
    };

    hash ^= hash >> 13;
    hash *= m;
    hash ^= hash >> 15;

    return hash;
}

//==================================================================================================================

template<typename key_t, typename data_t>
bool Hash_table<key_t, data_t>::set_value(key_t& key, data_t& value)
{
    size_t idx = hash_(key);

    Node<key_t, data_t>* list_elem = keys_[idx].find_value(key);

    if (list_elem == nullptr)
    {
        keys_[idx].push(key, value);
        ++size_;

        return true;
    }

    return false;
}

template<typename key_t, typename data_t>
std::optional<data_t> Hash_table<key_t, data_t>::get_value(key_t& key) const
{
    size_t idx = hash_(key);

    Node<key_t, data_t>* list_elem = keys_[idx].find_value(key);

    if (list_elem != nullptr)
    {
        return list_elem->data_;
    }

    return std::nullopt;
}

template<typename key_t, typename data_t>
void Hash_table<key_t, data_t>::remove(key_t& key)
{
    size_t idx = hash_(key);
    keys_[idx].delete_node(key);

    --size_;
}

template<typename key_t, typename data_t>
size_t Hash_table<key_t, data_t>::get_capacity() const
{
    return capacity_;
}

template<typename key_t, typename data_t>
size_t Hash_table<key_t, data_t>::get_size() const
{
    return size_;
}
}; // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_HASH_TABLE_IMPL_HPP_INCLUDED_
