#ifndef TYPO_CORRECTOR_TEACHING_MANAGER_HPP_INCLUDED_
#define TYPO_CORRECTOR_TEACHING_MANAGER_HPP_INCLUDED_

#include <string>
#include <vector>

namespace s1ky {
enum teaching_mode
{
    NOT_SELECTED = 0,
    TEACH        = 1,
    USE_TEACHED  = 2,
    EXIT         = 3
};

class Teaching_manager
{
public:
    constexpr static const char* LEARN_FILE_PATH         = "../texts_for_teaching/Night_shift.txt";
    constexpr static const char* DUMP_NAME_PATH          = "../typo_corrector/teaching_manager/TOKENS_DUMP.txt";
    constexpr static const char* TEXTS_FOR_TEACHING_PATH = "../texts_for_teaching";

    Teaching_manager() = default;
    Teaching_manager(const Teaching_manager& other) = delete;
    Teaching_manager(Teaching_manager&& other) noexcept;
    ~Teaching_manager() = default;

    Teaching_manager& operator=(const Teaching_manager& other) = delete;
    Teaching_manager& operator=(Teaching_manager&& other) noexcept;

    bool   get_tokens_for_teaching(std::vector<std::string>* words_for_learning, teaching_mode eaching_mode = NOT_SELECTED);
    size_t get_token_max_len() const;
    std::vector<std::string> get_tokens() const;
    void set_filename(const std::string& filename);

    void read_file();
    void parse_string_to_tokens();
    void make_dump(size_t begin_dump_idx = 0);
    void fill_tokens_from_dump();

    static bool  is_file_empty(const std::string& file_path);
    static int   choosing_teaching_mode();
    static void  get_texts_for_teaching(std::vector<std::string>* texts_names);

    static std::string choosing_teaching_text(std::vector<std::string>* texts_names);

private:
    std::string learn_file_path_;
    std::string file_buffer_;

    std::vector<std::string> tokens_;

    size_t token_max_length_ = 0;
};
} // namespace s1ky

#endif // TYPO_CORRECTOR_TEACHING_MANAGER_HPP_INCLUDED_
