#include "typo_corrector.hpp"

#include <cctype>
#include <fstream>
#include <iterator>
#include <string>

namespace s1ky {
void Typo_corrector::dictionaries_input_()
{
    size_t dictionary_max_len = MAX_LEN_DICTIONARY;

    if (max_token_length_ < MAX_LEN_DICTIONARY)
    {
        dictionary_max_len = max_token_length_;
    }

    word_len_dictionary_ = new Dictionary[dictionary_max_len] {};
    nmb_dictionaries_    = dictionary_max_len - MIN_LEN_DICTIONARY;

    for (size_t i = 0; i < nmb_dictionaries_; ++i) { word_len_dictionary_[i].word_len = MIN_LEN_DICTIONARY + i; }

    size_t len = 0;

    for (auto& it : tokens_)
    {
        if ((len = strlen(it.c_str())) > MIN_LEN_DICTIONARY)
        {
            word_len_dictionary_[find_dictionary_by_len_(len)].set_value(it, len);
        }
    }
}

size_t Typo_corrector::find_dictionary_by_len_(size_t word_len)
{
    for (size_t i = 0; i < nmb_dictionaries_; ++i)
    {
        if (word_len_dictionary_[i].word_len == word_len)
        {
            return i;
        }
    }

    return 0;
}

void Typo_corrector::test() {}
}; // namespace s1ky
