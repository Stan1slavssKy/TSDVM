#ifndef TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_
#define TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_

#include "./dictionary/dictionary.hpp"
#include "./learn_manager/learn_manager.hpp"

#include <vector>

namespace s1ky {
enum replacing_type
{
    REPLACE_ALL         = 1,
    REPLACE_SELECTIVELY = 2
};

class Typo_corrector
{
public:
    constexpr static size_t ACCEPTABLE_LEV_DIST   = 1;
    constexpr static size_t MIN_LEN_DICTIONARY    = 2;
    constexpr static size_t MAX_LEN_DICTIONARY    = 30;
    constexpr static size_t MIN_WORD_REPLACE_FREQ = 10;

    Typo_corrector();
    explicit Typo_corrector(size_t dictionary_max_len);
    Typo_corrector(const Typo_corrector& other) = delete;
    Typo_corrector(Typo_corrector&& other) noexcept;
    ~Typo_corrector();

    Typo_corrector& operator=(const Typo_corrector& other) = delete;

    Typo_corrector& operator=(Typo_corrector&& other) noexcept;

    void start_correcting(const std::string& input_text_path);

private:
    Learn_manager learn_manager_;

    std::vector<std::string> words_for_learning_;

    Dictionary* len_dictionaries_   = nullptr;
    size_t      nmb_dictionaries_   = 0;
    size_t      dictionary_max_len_ = 0;

    size_t find_dictionary_(size_t word_len) const;

    void dictionaries_input_();

    void replacing_words_(std::string* file_buffer, replacing_type answer);

    std::string find_replacement_word_(const std::string& token) const;

    static bool pair_comparator(std::pair<std::string, size_t> lhs, std::pair<std::string, size_t> rhs);
    
    static bool get_answer_();

    static void read_file_(const std::string& input_filename, std::string* buffer);
};
} // namespace s1ky

#endif // TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_
