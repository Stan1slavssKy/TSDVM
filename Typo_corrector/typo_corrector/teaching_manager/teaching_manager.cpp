#include "teaching_manager.hpp"

#include <cstring>
#include <fstream>
#include <iostream>
#include <iterator>

namespace s1ky {
void Teaching_manager::get_tokens_for_teaching(std::vector<std::string>* words_for_learning)
{
    int answer = choosing_teaching_mode_();

    if (answer == -1)
        return;
        
    if (answer == TEACH)
    {   
        std::cout << "Enter the name of the file from which you want to teach the dictionary: ";
        std::cin  >> learn_file_path_;

        learn_file_path_ = "../../texts_for_learn/" + learn_file_path_;

        read_file_();
        parse_();
        make_dump_();
        
        learn_file_path_ = DUMP_NAME;
        read_file_();
        fill_tokens_from_dump_();
    }
    else
    {
        if (is_file_empty_(DUMP_NAME))
        {
            learn_file_path_ = LEARN_FILE_PATH;
            read_file_();
            parse_();
            make_dump_();
        }
        else
        {
            learn_file_path_ = DUMP_NAME;
            read_file_();
            fill_tokens_from_dump_();
        }
    }

    *words_for_learning = tokens_;
}

int Teaching_manager::choosing_teaching_mode_()
{
    int answer = 0;

    while (true)
    {
        std::cout << "Which mode do you want to use? [by default - 2]\n"
                  << "1 - teach a dictionary\n"
                  << "2 - use an already teached dictionary\n"
                  << "3 - to exit\n";

        std::cin >> answer;
        if (answer == TEACH || answer == USE_TEACHED)
            return answer;

        if (answer == 3)
            return -1;

        std::cout << "You have entered an incorrect character. Try again.\n";
    }
}

void Teaching_manager::read_file_()
{
    std::ifstream file;
    file.open(learn_file_path_);

    if (!file.is_open())
    {
        std::cout << "Error, can't open " << learn_file_path_ << " file" << std::endl;
        return;
    }

    std::getline(file, file_buffer_, '\0');

    file.close();
}

void Teaching_manager::parse_()
{
    std::string token = " ";

    char*  beg_ptr = file_buffer_.data();
    char*  end_ptr = nullptr;
    size_t cur_len = 0;

    for (size_t idx = 0; idx < file_buffer_.size(); ++idx)
    {
        while(!isalpha(*beg_ptr) && *beg_ptr != '\0')
            ++beg_ptr;

        if (*beg_ptr == '\0')
            break;

        end_ptr = beg_ptr;

        while(isalpha(*end_ptr) || *end_ptr == '-')
            ++end_ptr;
        
        auto beg_pos = static_cast<size_t>(beg_ptr - file_buffer_.data());
        auto end_pos = static_cast<size_t>(end_ptr - beg_ptr);

        if ((end_pos - beg_pos) == 0)
            continue;

        token = file_buffer_.substr(beg_pos, end_pos);

        tokens_.push_back(token);

        if ((cur_len = strlen(token.c_str())) > token_max_length_)
            token_max_length_ = cur_len;
        
        if (*end_ptr == '\0')
            break;

        beg_ptr = end_ptr + 1;
    }
}

void Teaching_manager::make_dump_()
{
    std::ofstream file;
    file.open(DUMP_NAME, std::ios_base::app);

    if (!file.is_open())
    {
        std::cout << "Error, can't open " << DUMP_NAME << " file" << std::endl;
        return;
    }

    for (auto& it : tokens_)
    {
        file << it;
        file << " ";
    }

    file.close();
}

void Teaching_manager::fill_tokens_from_dump_()
{
    std::ifstream file(DUMP_NAME);

    if (!file.is_open())
    {
        std::cout << "Error, can't open " << DUMP_NAME << " file" << std::endl;
        return;
    }

    char*  beg_ptr = file_buffer_.data();
    char*  end_ptr = nullptr;
    size_t cur_len = 0;

    std::string token = " ";

    while (true)
    {
        while(*beg_ptr == ' ' || *beg_ptr == '\n')
            ++beg_ptr;

        if (*beg_ptr == '\0')
            break;

        end_ptr = beg_ptr;

        while(isalpha(*end_ptr) || *end_ptr == '-')
            ++end_ptr;

        auto beg_pos = static_cast<size_t>(beg_ptr - file_buffer_.data());
        auto end_pos = static_cast<size_t>(end_ptr - beg_ptr);

        if ((end_pos - beg_pos) == 0)
            continue;

        token = file_buffer_.substr(beg_pos, end_pos);

        tokens_.push_back(token);
        
        if ((cur_len = strlen(token.c_str())) > token_max_length_)
            token_max_length_ = cur_len;
        
        if (*end_ptr == '\0')
            break;

        beg_ptr = end_ptr + 1;
    }

    file.close();
}

bool Teaching_manager::is_file_empty_(const std::string& file_path)
{
    std::ifstream file(file_path);

    if (file)
    {
        return file.peek() == std::ifstream::traits_type::eof();
    }
    return true; 
}

size_t Teaching_manager::get_token_max_len() const
{
    return token_max_length_;
}
} // namespace s1ky
