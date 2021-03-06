#ifndef HASH_TABLE_HASH_TABLE_HASH_TABLE_HPP_INCLUDED_
#define HASH_TABLE_HASH_TABLE_HASH_TABLE_HPP_INCLUDED_

#include "../list/list_impl.hpp"

#include <cstdlib>
#include <optional>
#include <variant>
#include <vector>

namespace s1ky {
template<typename key_t, typename data_t>
class Hash_table
{
public:
    constexpr static size_t default_size = 1 << 18;

    Hash_table();
    Hash_table(size_t capacity);
    Hash_table(const Hash_table<key_t, data_t>& other) = delete;
    Hash_table(Hash_table<key_t, data_t>&& other) noexcept;
    ~Hash_table();

    Hash_table<key_t, data_t>& operator=(const Hash_table<key_t, data_t>& other) = delete;
    Hash_table<key_t, data_t>& operator=(Hash_table<key_t, data_t>&& other) noexcept;

    bool set_value(const key_t& key, const data_t& value);
    void remove(const key_t& key);

    std::optional<data_t> get_value(const key_t& key) const;

    size_t get_capacity() const;
    size_t get_size() const;

protected:
    size_t hash_(const key_t& key) const;

    size_t capacity_ = 0;
    size_t size_     = 0;

    List<key_t, data_t>* keys_ = nullptr;

    std::vector<Node<key_t, data_t>*> valid_nodes_;
};
} // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_HASH_TABLE_HPP_INCLUDED_
