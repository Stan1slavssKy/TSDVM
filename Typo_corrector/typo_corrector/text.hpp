#ifndef TYPO_CORRECTOR_TYPO_CORRECTOR_TEXT_HPP_INCLUDED_
#define TYPO_CORRECTOR_TYPO_CORRECTOR_TEXT_HPP_INCLUDED_

#include <string>
#include <vector>

namespace s1ky {
class Text
{
public:
    constexpr static const char* file_path = "../input_text";

    Text();
    explicit Text(const char* file_name);
    Text(const Text& other) = delete;
    Text(Text&& other) noexcept;
    ~Text() {};

    Text& operator=(const Text& other) = delete;
    Text& operator                     =(Text&& other) noexcept;

protected:
    std::string file_name_ = " ";

    std::string file_buffer_ = " ";

    std::vector<std::string> tokens_ = {};

    size_t max_token_length_ = 0;

    void read_file_();
    void parser_();
};
}; // namespace s1ky

#endif // TYPO_CORRECTOR_TYPO_CORRECTOR_TEXT_HPP_INCLUDED_
