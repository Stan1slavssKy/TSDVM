#include "typo_corrector.hpp"

#include <cctype>
#include <fstream>
#include <iterator>
#include <string>
#include <optional>

namespace s1ky {
Typo_corrector::Typo_corrector()
{
    read_file_();
    parser_();

    dictionary_max_len_ = MAX_LEN_DICTIONARY;

    if (max_token_length_ < MAX_LEN_DICTIONARY)
    {
        dictionary_max_len_ = max_token_length_;
    }

    word_len_dictionary_ = new Dictionary[dictionary_max_len_] {};

    nmb_dictionaries_ = dictionary_max_len_ - MIN_LEN_DICTIONARY;
}

Typo_corrector::~Typo_corrector()
{
    delete[] word_len_dictionary_;
}

Typo_corrector::Typo_corrector(size_t dictionary_max_len) : 
    nmb_dictionaries_(dictionary_max_len - MIN_LEN_DICTIONARY), 
    dictionary_max_len_(dictionary_max_len)
{
    read_file_();
    parser_();

    word_len_dictionary_ = new Dictionary[dictionary_max_len_] {};
}

Typo_corrector::Typo_corrector(Typo_corrector&& other) noexcept :
    word_len_dictionary_(other.word_len_dictionary_),
    nmb_dictionaries_(other.nmb_dictionaries_),
    dictionary_max_len_(other.dictionary_max_len_)
{
    other.word_len_dictionary_ = nullptr;
}

//=============================================================================================

Typo_corrector& Typo_corrector::operator=(Typo_corrector&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    std::swap(word_len_dictionary_, other.word_len_dictionary_);
    nmb_dictionaries_   = other.nmb_dictionaries_;
    dictionary_max_len_ = other.dictionary_max_len_;

    return *this;
}

//=============================================================================================

void Typo_corrector::dictionaries_input_()
{
    for (size_t i = 0; i < nmb_dictionaries_; ++i) 
    { 
        word_len_dictionary_[i].word_len = MIN_LEN_DICTIONARY + i; 
    }

    size_t len = 0;

    for (auto& it : tokens_)
    {
        if ((len = strlen(it.c_str())) > MIN_LEN_DICTIONARY)
        {
            size_t len_idx = find_dictionary_by_len_(len);
            size_t frequency = word_len_dictionary_[len_idx].get_value(it).value_or(0);

            if (frequency)
            {
                word_len_dictionary_[len_idx].set_value(it, ++frequency);
            }
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

void Typo_corrector::start_correcting()
{
    dictionaries_input_();
}
}; // namespace s1ky
