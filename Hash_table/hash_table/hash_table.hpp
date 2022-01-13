#ifndef HASH_TABLE_HASH_TABLE_HPP_INCLUDED
#define HASH_TABLE_HASH_TABLE_HPP_INCLUDED

#include "../queue/queue_impl.hpp"

#include <cstdlib>

using namespace s1ky::list_queue;

namespace s1ky {
template<typename key_t, typename data_t>
class Hash_table
{
public:
    constexpr static size_t default_size = 16; // here needs static cause class member does not exist at compile time
    constexpr static int    resize_coeff = 2;

    Hash_table();
    Hash_table(size_t size);
    Hash_table(const Hash_table<key_t, data_t>& other);
    Hash_table(Hash_table<key_t, data_t>&& other) noexcept;
    ~Hash_table();

    Hash_table<key_t, data_t>& operator=(const Hash_table<key_t, data_t>& other);
    Hash_table<key_t, data_t>& operator=(Hash_table<key_t, data_t>&& other) noexcept;

    bool find_value(const key_t value);

    void add(const key_t value);
    void remove();

private:
    size_t capacity_     = 0;
    size_t size_         = 0;
    Queue<data_t>* keys_ = nullptr; // an array that stores a pointer to a list of values

    size_t hash_(key_t key);
    void resize_();
};
}; // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_HPP_INCLUDED