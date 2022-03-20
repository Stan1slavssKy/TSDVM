#include "text.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>

namespace s1ky {
Text::Text() : file_name(FILE_PATH) {}

Text::Text(const char* file_name) : file_name(file_name) {}

Text::Text(Text&& other) noexcept :
    file_name(std::move(other.file_name)), file_buffer(std::move(other.file_buffer)), tokens(std::move(other.tokens))
{}

Text& Text::operator=(Text&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    std::swap(other.file_buffer, file_buffer);
    std::swap(other.file_name, file_name);
    std::swap(other.tokens, tokens);

    return *this;
}

//============================================================================================================

void Text::read_file()
{
    std::ifstream file;

    file.open(file_name);

    if (!file.is_open())
    {
        std::cout << "Error, can't open file" << std::endl;
        return;
    }

    std::getline(file, file_buffer, '\0');

    file.close();
}

void Text::parser()
{
    size_t begin_token = 0;
    size_t end_token   = 0;
    size_t cur_length  = 0;

    std::string       token = " ";
    std::string const delims { " .,:;!?\n()\"" };

    while ((begin_token = file_buffer.find_first_not_of(delims, end_token)) != std::string::npos)
    {
        end_token = file_buffer.find_first_of(delims, begin_token + 1);
        token     = file_buffer.substr(begin_token, end_token - begin_token);

        char& front = token.front();
        if (front == '\'')
        {
            token.erase(0, 1);
        }

        if (!token.empty())
        {
            char& back = token.back();
            if (back == '\'')
            {
                token.erase(token.size() - 1, 1);
            }
        }

        tokens.push_back(token);

        if ((cur_length = strlen(token.c_str())) > max_token_length)
        {
            max_token_length = cur_length;
        }
    }
}

std::string Text::get_lower_case(std::string& token)
{
    for (auto& it : token) { it = static_cast<char>(std::tolower(it)); }
    return token;
}
} // namespace s1ky
