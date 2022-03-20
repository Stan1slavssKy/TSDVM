#ifndef TYPO_CORRECTOR_TYPO_CORRECTOR_DICTIONARY_HPP_INCLUDED_
#define TYPO_CORRECTOR_TYPO_CORRECTOR_DICTIONARY_HPP_INCLUDED_

#include "../hash_table/hash_table_impl.hpp"

namespace s1ky {
class Dictionary : public Hash_table<std::string, size_t>
{
public:
    constexpr static size_t ACCEPTABLE_LEV_DIST = 1;

    std::string find_similar_word(const std::string& word) const;

    static size_t lev_distance_calculation(const std::string& lhs, const std::string& rhs);

    size_t word_len = 0;
};
} // namespace s1ky

#endif // TYPO_CORRECTOR_TYPO_CORRECTOR_DICTIONARY_HPP_INCLUDED_
