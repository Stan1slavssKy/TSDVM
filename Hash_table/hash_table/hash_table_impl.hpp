#ifndef HASH_TABLE_HASH_TABLE_IMPL_HPP
#define HASH_TABLE_HASH_TABLE_IMPL_HPP

#include "../queue/queue_impl.hpp"
#include "hash_table.hpp"

#include <cstring>
#include <iostream>
#include <string>

namespace s1ky {
template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table() : capacity_(default_size)
{
    keys_ = new Queue<data_t>[capacity_] {};
}

template<typename key_t, typename data_t>
Hash_table<key_t, data_t>::Hash_table(size_t capacity) : capacity_(capacity)
{
    keys_ = new Queue<data_t>[capacity_] {};
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
size_t Hash_table<key_t, data_t>::hash_(key_t key) const                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
{
    size_t hash_result = 0;

    return hash_result;
}

/*
template<>
size_t Hash_table<char*, char*>::hash_(char* key)
{
    size_t hash_result = 0;

    int idx = 0;

    while (key[idx] != '\0')
    {
        hash_result = (hash_result + static_cast<size_t>(key[idx])) % capacity_;
        ++idx;
    }

    hash_result = (hash_result * 2 + 1) % capacity_;

    return hash_result;
}
*/

template<typename key_t, typename data_t>
bool Hash_table<key_t, data_t>::find_value(const data_t value) const
{
    int idx = hash_(value);
    
    if ((keys_[idx])->find_value(value) != nullptr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

template<typename key_t, typename data_t>
void Hash_table<key_t, data_t>::add(const data_t value)
{
    if (size_ > capacity_)
    {
        std::cout << "Error, size > capacity" << std::endl;
        return;
    }

    if (find_value(value) == false)
    {
        int idx = hash_(value);
        (keys_[idx])->push(value);
    }
}

template<typename key_t, typename data_t>
void Hash_table<key_t, data_t>::remove(const data_t value)
{   
    int idx = hash_(value);
    (keys_[idx])->delete_value_node(value);
}

}; // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_IMPL_HPP