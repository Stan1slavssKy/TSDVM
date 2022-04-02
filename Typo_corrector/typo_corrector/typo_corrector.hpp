#ifndef TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_
#define TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_

#include "./dictionary/dictionary.hpp"
#include "./teaching_manager/teaching_manager.hpp"

#include <vector>

namespace s1ky {
class Typo_corrector
{
public:
    constexpr static size_t ACCEPTABLE_LEV_DIST = 1;
    constexpr static size_t MIN_LEN_DICTIONARY  = 2;
    constexpr static size_t MAX_LEN_DICTIONARY  = 30;

    enum replacement_type
    {
        NOT_SELECTED        = 0,
        REPLACE_ALL         = 1,
        REPLACE_SELECTIVELY = 2,
        EXIT                = 3
    };

    Typo_corrector();
    explicit Typo_corrector(size_t threads_number);
    Typo_corrector(const Typo_corrector& other) = delete;
    Typo_corrector(Typo_corrector&& other) noexcept;
    ~Typo_corrector();

    Typo_corrector& operator=(const Typo_corrector& other) = delete;
    Typo_corrector& operator                               =(Typo_corrector&& other) noexcept;

    void start_correcting(const std::string& input_text_path,
                          replacement_type   replacement_type = replacement_type::NOT_SELECTED,
                          teaching_mode      teaching_mode    = teaching_mode::NOT_SELECTED);

    void   replacing_words(std::string* file_buffer, replacement_type replacement_type);
    void   dictionaries_input();
    size_t find_dictionary(size_t word_len) const;

    std::string* find_replacement_word(std::string* token) const;

    static size_t get_number_dictionaries_for_iterations(size_t word_len);
    static bool   is_need_replace();
    static void   read_file(const std::string& input_filename, std::string* buffer);
    static int    choosing_replace_mode();

private:
    bool is_valid_ = false;

    Teaching_manager teaching_manager_;

    std::vector<std::string>   words_for_learning_;
    std::allocator<Dictionary> dict_alloc_;
    Dictionary*                len_dictionaries_;

    size_t nmb_dictionaries_   = 0;
    size_t dictionary_max_len_ = 0;
};
} // namespace s1ky

#endif // TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_
