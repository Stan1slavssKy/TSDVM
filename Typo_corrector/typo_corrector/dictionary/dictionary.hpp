#ifndef TYPO_CORRECTOR_TYPO_CORRECTOR_DICTIONARY_HPP_INCLUDED_
#define TYPO_CORRECTOR_TYPO_CORRECTOR_DICTIONARY_HPP_INCLUDED_

#include "../../hash_table/hash_table_impl.hpp"

#include <thread>
#include <vector>

namespace s1ky {
class Dictionary : public Hash_table<std::string, size_t>
{
public:
    constexpr static size_t ACCEPTABLE_LEV_DIST   = 1;
    constexpr static size_t MIN_WORD_REPLACE_FREQ = 10;

    Dictionary();
    Dictionary(size_t threads_number);
    Dictionary(const Dictionary& other) = delete;
    Dictionary(Dictionary&& other) noexcept;
    ~Dictionary() = default;

    Dictionary& operator=(const Dictionary& other) = delete;
    Dictionary& operator=(Dictionary&& other) noexcept;

    std::string* get_similar_word_thread(const std::string& token);

    void call_threads(const std::string& token, std::vector<std::pair<std::string*, size_t>>* suitable_words);
    void join_threads(std::vector<std::pair<std::string*, size_t>>* suitable_words,
                      std::vector<std::pair<std::string*, size_t>>* out_pair);

    std::string* find_similar_word(const std::string& word) const;
    void find_similar_word_thread(std::vector<std::pair<std::string*, size_t>>* out_pairs, const std::string& word,
                                  size_t beg_pos, size_t end_pos);

    static size_t       lev_distance_calculation(const std::string& lhs, const std::string& rhs);
    static std::string* find_best_word(std::vector<std::pair<std::string*, size_t>>* suitable_words_pair);

    size_t word_len                       = 0;
    size_t threads_number                 = 0;
    size_t nmb_iterations_per_thread      = 0;
    size_t nmb_iterations_for_last_thread = 0;

private:
    std::vector<std::thread> threads_;
};
} // namespace s1ky

#endif // TYPO_CORRECTOR_TYPO_CORRECTOR_DICTIONARY_HPP_INCLUDED_
