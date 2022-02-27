#ifndef TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_
#define TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_

#include "dictionary.hpp"
#include "text.hpp"

#include <vector>

namespace s1ky {
class Typo_corrector : public Text
{
public:
    constexpr static size_t MIN_LEN_DICTIONARY = 2;
    constexpr static size_t MAX_LEN_DICTIONARY = 30;

    void test();
    void start_correcting();

private:
    Dictionary* word_len_dictionary_ = nullptr;
    size_t      nmb_dictionaries_    = 0;

    size_t find_dictionary_by_len_(size_t word_len);
    void   dictionaries_input_();
};
}; // namespace s1ky

#endif // TYPO_CORRECTOR_TYPO_CORRECTOR_TYPO_CORRECTOR_HPP_INCLUDED_
