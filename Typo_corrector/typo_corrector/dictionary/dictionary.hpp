#ifndef TYPO_CORRECTOR_TYPO_CORRECTOR_DICTIONARY_HPP_INCLUDED_
#define TYPO_CORRECTOR_TYPO_CORRECTOR_DICTIONARY_HPP_INCLUDED_

#include "../../hash_table/hash_table_impl.hpp"

#include <thread>
#include <vector>

namespace s1ky {
class Dictionary : public Hash_table<std::string, size_t>
{
public:
    constexpr static size_t ACCEPTABLE_LEV_DIST = 1;

    Dictionary();
    Dictionary(size_t threads_number);
    Dictionary(const Dictionary& other) = delete;
    Dictionary(Dictionary&& other) noexcept;
    ~Dictionary() = default;

    Dictionary& operator=(const Dictionary& other) = delete;

    Dictionary& operator=(Dictionary&& other) noexcept;

    std::vector<std::pair<std::string, size_t>> get_similar_word_thread(const std::string& token);

    void call_threads_(const std::string& token, std::vector<std::string>* suitable_words);

    void join_threads_(std::vector<std::string>* suitable_words, 
                       std::vector<std::pair<std::string, size_t>>* output);

    static void find_similar_word_thread(const std::vector<Node<std::string, size_t>*>& input_vector,
                                         std::vector<std::string>* out_vector,
                                         const std::string& word, size_t beg_pos, size_t end_pos);

    std::vector<std::pair<std::string, size_t>> find_similar_word(const std::string& word) const;

    static size_t lev_distance_calculation(const std::string& lhs, const std::string& rhs);

    size_t word_len = 0;

private:
    size_t threads_number_ = 0;

    size_t nmb_iterations_per_thread_ = 0;

    size_t nmb_iterations_for_last_thread_ = 0;

    std::vector<std::thread> threads_;
};
} // namespace s1ky

#endif // TYPO_CORRECTOR_TYPO_CORRECTOR_DICTIONARY_HPP_INCLUDED_
