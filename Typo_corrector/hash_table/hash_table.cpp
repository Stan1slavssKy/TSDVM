#include "hash_table.hpp"

namespace s1ky {
Hash_table<std::string, size_t>::Hash_table() : capacity_(default_size)
{
    keys_ = new List<std::string, size_t>[capacity_] {};
}

Hash_table<std::string, size_t>::Hash_table(size_t capacity) : capacity_(capacity)
{
    keys_ = new List<std::string, size_t>[capacity_] {};
}

Hash_table<std::string, size_t>::Hash_table(Hash_table<std::string, size_t>&& other) noexcept :
    capacity_(other.capacity_), size_(other.size_), keys_(other.keys_)
{
    other.keys_ = nullptr;
}

Hash_table<std::string, size_t>::~Hash_table()
{
    delete[] keys_;
}

//==================================================================================================================

Hash_table<std::string, size_t>& Hash_table<std::string, size_t>::operator=(
    Hash_table<std::string, size_t>&& other) noexcept
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

size_t Hash_table<std::string, size_t>::hash_(std::string key) const
{
    return murmur_hash2(key) % capacity_;
}

size_t Hash_table<std::string, size_t>::murmur_hash2(std::string key) const
{
    const size_t m    = 0x5bd1e995;
    const size_t seed = 0xbc9f1d34;

    const unsigned char* data = reinterpret_cast<const unsigned char*>(key.c_str());

    size_t len  = strlen(key.c_str());
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

void Hash_table<std::string, size_t>::set_value(std::string key, size_t value)
{
    size_t idx = hash_(key);

    Node<std::string, size_t>* list_elem = keys_[idx].find_value(key);

    if (list_elem == nullptr)
    {
        keys_[idx].push(key, value);
        ++size_;
    }
    else
    {
        std::cout << "The key " << list_elem->key_ << " is already in the hash table" << std::endl;
    }
}

std::optional<size_t> Hash_table<std::string, size_t>::get_value(std::string key) const
{
    size_t idx = hash_(key);

    Node<std::string, size_t>* list_elem = keys_[idx].find_value(key);

    if (list_elem != nullptr)
    {
        return list_elem->data_;
    }

    return std::nullopt;
}

void Hash_table<std::string, size_t>::remove(std::string key)
{
    size_t idx = hash_(key);
    keys_[idx].delete_node(key);

    --size_;
}

size_t Hash_table<std::string, size_t>::get_capacity() const
{
    return capacity_;
}

size_t Hash_table<std::string, size_t>::get_size() const
{
    return size_;
}
}; // namespace s1ky