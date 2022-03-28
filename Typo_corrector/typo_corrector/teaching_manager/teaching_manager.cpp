#include "teaching_manager.hpp"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>

namespace s1ky {
bool Teaching_manager::get_tokens_for_teaching(std::vector<std::string>* words_for_learning)
{
    int answer = choosing_teaching_mode_();

    if (answer == EXIT)
        return false;

    size_t beg_dump_idx = 0;

    if (is_file_empty_(DUMP_NAME_PATH))
    {
        learn_file_path_ = LEARN_FILE_PATH;
        read_file_();
        parse_string_to_tokens_();

        if (answer == USE_TEACHED)
            make_dump_();
    }
    else
    {
        learn_file_path_ = DUMP_NAME_PATH;
        read_file_();
        fill_tokens_from_dump_();
        beg_dump_idx = tokens_.size();
    }

    if (answer == TEACH)
    {
        std::vector<std::string> texts_for_teaching;
        get_texts_for_teaching_(&texts_for_teaching);

        learn_file_path_ = choosing_teaching_text_(&texts_for_teaching);

        learn_file_path_ = "../../texts_for_teaching/" + learn_file_path_;
        read_file_();

        parse_string_to_tokens_();
        make_dump_(beg_dump_idx);
    }

    *words_for_learning = tokens_;
    return true;
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
        std::cout << "\n";

        if (answer == TEACH || answer == USE_TEACHED)
            return answer;

        if (answer == EXIT)
            return EXIT;
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "You have entered an incorrect character. Try again." << std::endl;
    }
}

void Teaching_manager::get_texts_for_teaching_(std::vector<std::string>* texts_names)
{
    std::string path = TEXTS_FOR_TEACHING_PATH;

    for (const auto& dir_entry : std::filesystem::directory_iterator(path))
    {
        texts_names->push_back(dir_entry.path().filename());
    }
}

const std::string& Teaching_manager::choosing_teaching_text_(std::vector<std::string>* texts_names)
{
    std::string answer;

    while (true)
    {
        std::cout << "Texts available for dictionary teaching:\n";

        for (auto& it : *texts_names)
        {
            std::cout << " - " << it;

            if (!strcmp(it.c_str(), "Night_shift.txt"))
                std::cout << " (this one is teached by default)";

            std::cout << "\n";
        }

        std::cout << "\n";
        std::cout << "Enter the name of the file from which you want to teach the dictionary: ";
        std::cin >> answer;
        std::cout << "\n";

        for (auto& it : *texts_names)
        {
            if (!strcmp(it.c_str(), answer.c_str()))
                return it;
        }

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

void Teaching_manager::make_dump_(size_t begin_dump_idx)
{
    std::ofstream file;
    file.open(DUMP_NAME_PATH, std::ios_base::app);

    if (!file.is_open())
    {
        std::cout << "Error, can't open " << DUMP_NAME_PATH << " file" << std::endl;
        return;
    }

    for (size_t idx = begin_dump_idx; idx < tokens_.size(); ++idx)
    {
        file << tokens_[idx];
        file << " ";
    }

    file.close();
}

void Teaching_manager::fill_tokens_from_dump_()
{
    std::ifstream file(DUMP_NAME_PATH);

    if (!file.is_open())
    {
        std::cout << "Error, can't open " << DUMP_NAME_PATH << " file" << std::endl;
        return;
    }

    parse_string_to_tokens_();

    file.close();
}

void Teaching_manager::parse_string_to_tokens_()
{
    char*  beg_ptr = file_buffer_.data();
    char*  end_ptr = nullptr;
    size_t cur_len = 0;

    std::string token = " ";

    while (true)
    {
        while (!isalpha(*beg_ptr) && *beg_ptr != '\0')
            ++beg_ptr;

        if (*beg_ptr == '\0')
            break;

        end_ptr = beg_ptr;

        while (isalpha(*end_ptr) || *end_ptr == '-') ++end_ptr;

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
