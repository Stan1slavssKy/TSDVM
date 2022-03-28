#ifndef TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_
#define TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_

#include "./dictionary/dictionary.hpp"
#include "./teaching_manager/teaching_manager.hpp"

#include <vector>

namespace s1ky {
class Typo_corrector
{
public:
    constexpr static size_t ACCEPTABLE_LEV_DIST   = 1;
    constexpr static size_t MIN_LEN_DICTIONARY    = 2;
    constexpr static size_t MAX_LEN_DICTIONARY    = 30;
    constexpr static size_t MIN_WORD_REPLACE_FREQ = 10;

    enum replacement_type
    {
        REPLACE_ALL         = 1,
        REPLACE_SELECTIVELY = 2,
        EXIT = 3
    };

    Typo_corrector();
    explicit Typo_corrector(size_t dictionary_max_len);
    Typo_corrector(const Typo_corrector& other) = delete;
    Typo_corrector(Typo_corrector&& other) noexcept;
    ~Typo_corrector();

    Typo_corrector& operator=(const Typo_corrector& other) = delete;

    Typo_corrector& operator=(Typo_corrector&& other) noexcept;

    void start_correcting(const std::string& input_text_path);
    void replacing_words(std::string* file_buffer, replacement_type replacement_type);

private:
    Teaching_manager teaching_manager_;

    std::vector<std::string> words_for_learning_;

    Dictionary* len_dictionaries_   = nullptr;
    size_t      nmb_dictionaries_   = 0;
    size_t      dictionary_max_len_ = 0;

    bool is_valid_ = false;

    size_t find_dictionary_(size_t word_len) const;

    void dictionaries_input_();

    std::string find_replacement_word_(const std::string& token) const;

    static bool pair_comparator(std::pair<std::string, size_t> lhs, std::pair<std::string, size_t> rhs);

    static bool is_need_replace_();

    static void read_file_(const std::string& input_filename, std::string* buffer);

    static int choosing_replace_mode_();
};
} // namespace s1ky

#endif // TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_
