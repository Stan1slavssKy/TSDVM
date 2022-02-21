#include "typo_corrector.hpp"

#include <cctype>
#include <fstream>
#include <iterator>
#include <string>

namespace s1ky {
void Typo_corrector::test()
{
    read_file_();
    parser_();
}

void Typo_corrector::read_file_()
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

void Typo_corrector::parser_()
{
    std::cout << file_buffer_ << std::endl;

    size_t begin_token = 0;
    size_t end_token   = 0;

    std::string token = " ";

    std::string const delims{ " .,:;!?'\n" };

    while((begin_token = file_buffer_.find_first_not_of(delims, end_token)) != std::string::npos)
    {
        end_token = file_buffer_.find_first_of(delims, begin_token + 1);
        token     = file_buffer_.substr(begin_token, end_token - begin_token);

        tokens_.push_back(token);
    }
}
}; // namespace s1ky
