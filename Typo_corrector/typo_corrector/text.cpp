#include "text.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>

namespace s1ky {
Text::Text() : file_name_(file_path) {}

Text::Text(const char* file_name) : file_name_(file_name) {}

Text::Text(Text&& other) noexcept :
    file_name_(std::move(other.file_name_)), file_buffer_(std::move(other.file_buffer_)),
    tokens_(std::move(other.tokens_))
{}

Text& Text::operator=(Text&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    std::swap(other.file_buffer_, file_buffer_);
    std::swap(other.file_name_, file_name_);
    std::swap(other.tokens_, tokens_);

    return *this;
}

//============================================================================================================

void Text::read_file_()
{
    const char*   file_name = "../input_text.txt";
    std::ifstream file;

    file.open(file_name);

    if (!file.is_open())
    {
        std::cout << "Error, can't open file" << std::endl;
        return;
    }

    std::getline(file, file_buffer_, '\0');

    file.close();
}

void Text::parser_()
{
    size_t begin_token = 0;
    size_t end_token   = 0;
    size_t cur_length  = 0;

    std::string       token = " ";
    std::string const delims { " .,:;!?'\n" };

    while ((begin_token = file_buffer_.find_first_not_of(delims, end_token)) != std::string::npos)
    {
        end_token = file_buffer_.find_first_of(delims, begin_token + 1);
        token     = file_buffer_.substr(begin_token, end_token - begin_token);

        tokens_.push_back(token);

        if ((cur_length = strlen(token.c_str())) > max_token_length_)
        {
            max_token_length_ = cur_length;
        }
    }
}
}; // namespace s1ky