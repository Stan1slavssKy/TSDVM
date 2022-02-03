#ifndef HASH_TABLE_HASH_TABLE_HPP_INCLUDED
#define HASH_TABLE_HASH_TABLE_HPP_INCLUDED

#include "../list/list_impl.hpp"

#include <cstdlib>
#include <optional>

namespace s1ky {
template<typename key_t, typename data_t>
class Hash_table
{
public:
    constexpr static size_t default_size = 16;

    Hash_table();
    Hash_table(size_t capacity);
    Hash_table(const Hash_table<key_t, data_t>& other) = delete;
    Hash_table(Hash_table<key_t, data_t>&& other) noexcept;
    ~Hash_table();

    Hash_table<key_t, data_t>& operator=(const Hash_table<key_t, data_t>& other) = delete;
    Hash_table<key_t, data_t>& operator=(Hash_table<key_t, data_t>&& other) noexcept;

    void set_value(key_t key, data_t value);
    void remove(key_t key);

    std::optional<data_t> get_value(key_t key) const;

    unsigned int murmur_hash2(data_t key) const;

private:
    size_t capacity_ = 0;
    size_t size_     = 0;

    List<key_t, data_t>* keys_ = nullptr;

    unsigned int hash_(key_t key) const;
};
}; // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_HPP_INCLUDED
