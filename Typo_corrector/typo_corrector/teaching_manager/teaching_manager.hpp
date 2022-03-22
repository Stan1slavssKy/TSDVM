#ifndef TYPO_CORRECTOR_TEACHING_MANAGER_HPP_INCLUDED_
#define TYPO_CORRECTOR_TEACHING_MANAGER_HPP_INCLUDED_

#include <string>
#include <vector>

namespace s1ky {
enum teaching_mode
{
    TEACH = 1,
    USE_TEACHED = 2
};

class Teaching_manager
{
public:
    constexpr static const char* LEARN_FILE_PATH = "../../texts_for_learn/dictionary_text.txt";
    constexpr static const char* DUMP_NAME = "../../typo_corrector/teaching_manager/TOKENS_DUMP.txt";

    void get_tokens_for_teaching(std::vector<std::string>* words_for_learning);
    
    size_t get_token_max_len() const;

private:
    std::string learn_file_path_;
    std::string file_buffer_;

    std::vector<std::string> tokens_;

    size_t token_max_length_;

    void read_file_();

    void parse_();

    void make_dump_();

    void fill_tokens_from_dump_();

    static bool is_file_empty_(const std::string& file_path);
    static int  choosing_teaching_mode_();
};
} // namespace s1ky

#endif // TYPO_CORRECTOR_TEACHING_MANAGER_HPP_INCLUDED_