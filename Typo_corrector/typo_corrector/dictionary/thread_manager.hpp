#ifndef TYPO_CORRECOTR_TYPO_CORRECTOR_DICTIONARY_THREAD_MANAGER_HPP_INCLUDED_
#define TYPO_CORRECOTR_TYPO_CORRECTOR_DICTIONARY_THREAD_MANAGER_HPP_INCLUDED_

#include "dictionary.hpp"

#include <thread>

namespace s1ky {
class Dictionary::Thread_manager
{
public:
    Thread_manager();
    explicit Thread_manager(size_t threads_number);
    Thread_manager(const Thread_manager& other) = delete;
    Thread_manager(Thread_manager&& other) noexcept;
    ~Thread_manager();

    Dictionary::Thread_manager& operator=(const Thread_manager& other) = delete;

    Dictionary::Thread_manager& operator=(Thread_manager&& other) noexcept;

    std::vector<std::pair<std::string, size_t>> get_similar_word_thread(const std::string& token);

    void find_similar_word_thread(std::vector<std::pair<std::string, size_t>>* out_vector, const std::string& word,
                                         size_t beg_pos, size_t end_pos);

private:
    size_t threads_number_ = 0;

    size_t nmb_iterations_per_thread_ = 0;

    size_t nmb_iterations_for_last_thread_ = 0;

    std::vector<std::thread> threads_;
};
} // namespace s1ky

#endif // TYPO_CORRECOTR_TYPO_CORRECTOR_DICTIONARY_THREAD_MANAGER_HPP_INCLUDED_