#ifndef HASH_TABLE_HASH_TABLE_HPP_INCLUDED
#define HASH_TABLE_HASH_TABLE_HPP_INCLUDED

#include <cstdlib>

namespace s1ky 
{
template<typename key_t, typename data_t>
class Hash_table
{
public:
    constexpr static size_t default_size = 16;
    constexpr static int    rehash_size  = 2;

    Hash_table();
    Hash_table(size_t size);
    Hash_table(const Hash_table<key_t, data_t>& other);
    Hash_table(Hash_table<key_t, data_t>&& other) noexcept;
    ~Hash_table();
    
    Hash_table<key_t, data_t>& operator=(const Hash_table<key_t, data_t>& other);
    Hash_table<key_t, data_t>&& operator=(Hash_table<key_t, data_t>&& other) noexcept;
    
    int hash(const key_t key);

private:
    size_t size_ = 0; // size without deleted values
    key_t* keys_ = nullptr;  
};
}; // namespace s1ky

#endif // HASH_TABLE_HASH_TABLE_HPP_INCLUDED