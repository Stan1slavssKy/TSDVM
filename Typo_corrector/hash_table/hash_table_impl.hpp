#ifndef HASH_TABLE_HASH_TABLE_HASH_TABLE_IMPL_HPP_INCLUDED_
#define HASH_TABLE_HASH_TABLE_HASH_TABLE_IMPL_HPP_INCLUDED_

#include "../list/list_impl.hpp"
#include "hash_table.hpp"

#include <cstring>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <type_traits>
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
    capacity_(other.capacity_), size_(other.size_), keys_(other.keys_), valid_nodes_(other.valid_nodes_)
{
    other.keys_        = nullptr;
    other.valid_nodes_ = nullptr;
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
        return *this;

    size_     = other.size_;
    capacity_ = other.capacity_;

    std::swap(keys_, other.keys_);
    std::swap(valid_nodes_, other.valid_nodes_);

    return *this;
}

//==================================================================================================================

template<typename key_t, typename data_t>
size_t Hash_table<key_t, data_t>::hash_(const key_t& key) const
{
    return (std::hash<key_t>{}(key)) % capacity_;
}

template<typename key_t, typename data_t>
bool Hash_table<key_t, data_t>::set_value(const key_t& key, const data_t& value)
{
    size_t idx = hash_(key);

    Node<key_t, data_t>* list_elem = keys_[idx].find_value(key);

    if (list_elem == nullptr)
    {
        Node<key_t, data_t>* is_new_list = keys_[idx].push(key, value);

        if (is_new_list != nullptr)
        {
            valid_nodes_.push_back(is_new_list);
        }

        ++size_;

        return true;
    }

    list_elem->data_ = value;

    return false;
}

template<typename key_t, typename data_t>
std::optional<data_t> Hash_table<key_t, data_t>::get_value(const key_t& key) const
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
void Hash_table<key_t, data_t>::remove(const key_t& key)
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
} // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_HASH_TABLE_IMPL_HPP_INCLUDED_
