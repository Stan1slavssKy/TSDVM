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
    read_file();
    parser();

    dictionary_max_len_ = MAX_LEN_DICTIONARY;

    if (max_token_length < MAX_LEN_DICTIONARY)
    {
        dictionary_max_len_ = max_token_length;
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
    read_file();
    parser();

    len_dictionaries_ = new Dictionary[dictionary_max_len_] {};
}

Typo_corrector::Typo_corrector(const char* teaching_text_path) : Text(teaching_text_path)
{
    read_file();
    parser();

    dictionary_max_len_ = MAX_LEN_DICTIONARY;

    if (max_token_length < MAX_LEN_DICTIONARY)
    {
        dictionary_max_len_ = max_token_length;
    }

    len_dictionaries_ = new Dictionary[dictionary_max_len_] {};

    nmb_dictionaries_ = dictionary_max_len_ - MIN_LEN_DICTIONARY;
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

    for (auto& it : tokens)
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

void Typo_corrector::start_correcting(const char* input_text_path)
{
    dictionaries_input_();

    std::string input_filename  = input_text_path;
    std::string output_filename = input_filename.substr(0, input_filename.find_last_of('.'));

    output_filename = output_filename + "_output.txt";

    std::cout << output_filename << std::endl;

    std::cout << "Press\n"
              << "1 - If you want to replace all typos at once\n"
              << "2 - If you want to replace typos selectively\n"
              << "By default, 1 is provided" << std::endl;

    int answer = REPLACE_ALL;
    std::cin >> answer;

    std::string output_str = replacing_words_(input_text_path, static_cast<replacing_type>(answer));

    std::ofstream out(output_filename);
    out << output_str;
    out.close();
}

std::string Typo_corrector::replacing_words_(const char* input_filename, replacing_type answer)
{
    Text input_file(input_filename);
    input_file.read_file();
    input_file.parser();
    std::string input_buffer = input_file.file_buffer;

    size_t begin_token = 0;
    size_t end_token   = 0;

    std::string       token = " ";
    std::string const delims { " .,:;!?\n()\"" };

    while ((begin_token = input_buffer.find_first_not_of(delims, end_token)) != std::string::npos)
    {
        end_token = input_buffer.find_first_of(delims, begin_token + 1);
        token     = input_buffer.substr(begin_token, end_token - begin_token);

        char& front = token.front();
        if (front == '\'')
        {
            token.erase(0, 1);
            ++begin_token;
        }

        if (!token.empty())
        {
            char& back = token.back();
            if (back == '\'')
            {
                token.erase(token.size() - 1, 1);
            }
        }

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

            input_buffer.replace(begin_token, token.size(), sim_word.c_str());
        }
    }

    return input_buffer;
}

std::string Typo_corrector::find_replacement_word_(const std::string& token) const
{
    size_t len = std::strlen(token.c_str());

    std::vector<std::pair<std::string, size_t>> frequency;

    size_t max_dict_idx = 0;

    if (len < 2)
    {
        return token;
    }

    if (len > 2)
    {
        max_dict_idx = 2 * ACCEPTABLE_LEV_DIST + 1;
    }
    else if (len == 2)
    {
        return token;
    }

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
} // namespace s1ky
