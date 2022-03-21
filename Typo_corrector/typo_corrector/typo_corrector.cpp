#include "typo_corrector.hpp"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <optional>
#include <string>

namespace s1ky {
Typo_corrector::Typo_corrector()
{
    learn_manager_.get_tokens_for_learn(&words_for_learning_);

    dictionary_max_len_ = MAX_LEN_DICTIONARY;

    if (learn_manager_.get_token_max_len() < MAX_LEN_DICTIONARY)
    {
        dictionary_max_len_ = learn_manager_.get_token_max_len();
    }

    len_dictionaries_ = new Dictionary[dictionary_max_len_] {};

    nmb_dictionaries_ = dictionary_max_len_ - MIN_LEN_DICTIONARY;
}

Typo_corrector::~Typo_corrector()
{
    delete[] len_dictionaries_;
}

Typo_corrector::Typo_corrector(size_t dictionary_max_len) :
    nmb_dictionaries_(dictionary_max_len - MIN_LEN_DICTIONARY), dictionary_max_len_(dictionary_max_len)
{
    learn_manager_.get_tokens_for_learn(&words_for_learning_);

    len_dictionaries_ = new Dictionary[dictionary_max_len_] {};
}

Typo_corrector::Typo_corrector(Typo_corrector&& other) noexcept :
    len_dictionaries_(other.len_dictionaries_), nmb_dictionaries_(other.nmb_dictionaries_),
    dictionary_max_len_(other.dictionary_max_len_)
{
    other.len_dictionaries_ = nullptr;
}

//=============================================================================================

Typo_corrector& Typo_corrector::operator=(Typo_corrector&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    std::swap(len_dictionaries_, other.len_dictionaries_);

    nmb_dictionaries_   = other.nmb_dictionaries_;
    dictionary_max_len_ = other.dictionary_max_len_;

    return *this;
}

//=============================================================================================

void Typo_corrector::dictionaries_input_()
{
    for (size_t i = 0; i < nmb_dictionaries_; ++i) { len_dictionaries_[i].word_len = MIN_LEN_DICTIONARY + i; }

    size_t len = 0;

    for (auto& it : words_for_learning_)
    {
        size_t len_idx   = 0;
        size_t frequency = 0;

        if ((len = strlen(it.c_str())) > MIN_LEN_DICTIONARY)
        {
            len_idx   = find_dictionary_(len);
            frequency = len_dictionaries_[len_idx].get_value(it).value_or(0);
            len_dictionaries_[len_idx].set_value(it, ++frequency);
        }
    }
}

size_t Typo_corrector::find_dictionary_(size_t word_len) const
{
    for (size_t i = 0; i < nmb_dictionaries_; ++i)
    {
        if (len_dictionaries_[i].word_len == word_len)
        {
            return i;
        }
    }

    return 0;
}

void Typo_corrector::start_correcting(const std::string& input_text_path)
{
    dictionaries_input_();

    std::string output_filename = input_text_path.substr(0, input_text_path.find_last_of('.'));

    output_filename = output_filename + "_output.txt";

    std::cout << "Press\n"
              << "1 - If you want to replace all typos at once\n"
              << "2 - If you want to replace typos selectively\n"
              << "By default, 1 is provided" << std::endl;

    int answer = REPLACE_ALL;
    std::cin >> answer;

    std::string file_buffer;
    read_file_(input_text_path, &file_buffer);

    replacing_words_(&file_buffer, static_cast<replacing_type>(answer));

    std::ofstream out(output_filename);
    out << file_buffer;
    out.close();
}

void Typo_corrector::replacing_words_(std::string* file_buffer, replacing_type answer)
{
    std::string token = " ";

    char*  beg_ptr = file_buffer->data();
    char*  end_ptr = nullptr;

    for (size_t idx = 0; idx < file_buffer->size(); ++idx)
    {
        while(!isalpha(*beg_ptr) && *beg_ptr != '\0')
            ++beg_ptr;

        if (*beg_ptr == '\0')
            break;

        end_ptr = beg_ptr;

        while(isalpha(*end_ptr) || *end_ptr == '-')
            ++end_ptr;
        
        auto beg_pos = static_cast<size_t>(beg_ptr - file_buffer->data());
        auto end_pos = static_cast<size_t>(end_ptr - beg_ptr);

        if ((end_pos - beg_pos) == 0)
            continue;

        token = file_buffer->substr(beg_pos, end_pos);
        
        if (*end_ptr == '\0')
            break;

        beg_ptr = end_ptr + 1;

        if (!token.empty())
        {
            std::string sim_word = find_replacement_word_(token);

            if ((answer == REPLACE_SELECTIVELY) && (strcmp(sim_word.c_str(), token.c_str()) != 0))
            {
                std::cout << "Would you like to replace " << token << " ---> " << sim_word << "[y/n]" << std::endl;
                if (get_answer_()) {}

                else
                {
                    continue;
                }
            }
            file_buffer->replace(beg_pos, token.size(), sim_word.c_str());
        }
    }
}

std::string Typo_corrector::find_replacement_word_(const std::string& token) const
{
    size_t len = std::strlen(token.c_str());

    std::vector<std::pair<std::string, size_t>> frequency;

    size_t max_dict_idx = 0;

    if (len < 2)
        return token;

    if (len > 2)
        max_dict_idx = 2 * ACCEPTABLE_LEV_DIST + 1;

    else if (len == 2)
        return token;

    for (size_t i = 0; i < max_dict_idx; ++i)
    {
        size_t len_idx = len - MIN_LEN_DICTIONARY - ACCEPTABLE_LEV_DIST + i;

        if (len == 2)
        {
            len_idx += 1;
        }

        std::string cur_word = len_dictionaries_[len_idx].find_similar_word(token);

        if (cur_word.empty())
            continue;

        if (!strcmp(token.c_str(), cur_word.c_str()))
            return token;

        size_t cur_freq = len_dictionaries_[len_idx].get_value(cur_word).value_or(0);

        if (cur_freq == 0)
            continue;

        frequency.emplace_back(std::make_pair(cur_word, cur_freq));
    }

    if (frequency.empty())
    {
        return token;
    }

    std::sort(frequency.begin(), frequency.end(), pair_comparator);

    if (std::get<1>(frequency.front()) < MIN_WORD_REPLACE_FREQ)
    {
        return token;
    }

    std::string similar_word = std::get<0>(frequency.front());

    return similar_word;
}

bool Typo_corrector::pair_comparator(std::pair<std::string, size_t> lhs, std::pair<std::string, size_t> rhs)
{
    return (std::get<1>(lhs) < std::get<1>(rhs));
}

bool Typo_corrector::get_answer_()
{
    std::string answer;
    std::cin >> answer;

    return strcmp("y", answer.c_str()) == 0 || strcmp("yes", answer.c_str()) == 0;
}

void Typo_corrector::read_file_(const std::string& input_filename, std::string* buffer)
{
    std::ifstream file(input_filename);
    if (!file.is_open())
    {
        std::cout << "Error, can't open " << input_filename << " file" << std::endl;
        return;
    }
    std::getline(file, *buffer, '\0');
}
} // namespace s1ky
