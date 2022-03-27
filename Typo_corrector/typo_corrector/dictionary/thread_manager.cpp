#include "thread_manager.hpp"

#include <string>

namespace s1ky {
Dictionary::Thread_manager::Thread_manager()
{
    threads_number_ = std::thread::hardware_concurrency();

    nmb_iterations_per_thread_ = valid_lists_.size() / threads_number_;

    nmb_iterations_for_last_thread_ = nmb_iterations_per_thread_ + valid_lists_.size() % threads_number_;
}

Dictionary::Thread_manager::Thread_manager(size_t threads_number) : threads_number_(threads_number)
{
    threads_number_ = std::thread::hardware_concurrency();

    nmb_iterations_per_thread_ = valid_lists_.size() / threads_number_;

    nmb_iterations_for_last_thread_ = nmb_iterations_per_thread_ + valid_lists_.size() % threads_number_;
}

Dictionary::Thread_manager::Thread_manager(Thread_manager&& other) noexcept :
    threads_number_(other.threads_number_), nmb_iterations_per_thread_(other.nmb_iterations_per_thread_),
    nmb_iterations_for_last_thread_(other.nmb_iterations_for_last_thread_)
{
    std::swap(threads_, other.threads_);
}

Dictionary::Thread_manager& Dictionary::Thread_manager::operator=(Thread_manager&& other) noexcept
{
    std::swap(threads_, other.threads_);

    threads_number_                 = other.threads_number_;
    nmb_iterations_per_thread_      = other.nmb_iterations_per_thread_;
    nmb_iterations_for_last_thread_ = other.nmb_iterations_for_last_thread_;
}

//=========================================================================================================================

std::vector<std::pair<std::string, size_t>> Dictionary::Thread_manager::get_similar_word_thread(const std::string& token)
{
    std::vector<std::pair<std::string, size_t>> suitable_words[threads_number_];
    std::vector<std::pair<std::string, size_t>> output;
 
    for (size_t i = 0; i < threads_number_; ++i)
    {
        threads_.push_back(std::thread(find_similar_word_thread, &suitable_words[i], token, 0, 1));
    }

    for (size_t i = 0; i < threads_number_; ++i) { threads_[i].join(); }

    for (size_t i = 0; i < threads_number_; ++i)
    {
        for (auto& vec_it : suitable_words[i])
            output.emplace_back(vec_it);
    }

    return output;
}

void Dictionary::Thread_manager::find_similar_word_thread(std::vector<std::pair<std::string, size_t>>* out_vector,
                                                          const std::string& word, size_t beg_pos, size_t end_pos)
{
    for (size_t i = beg_pos; i < end_pos; ++i)
    {
        for (auto& l_it : valid_lists_[i])
        {
            if (!strcmp(word.c_str(), l_it.key_.c_str()))
                return;

            size_t lev_dist = lev_distance_calculation(word, (l_it.key_));

            if (lev_dist <= ACCEPTABLE_LEV_DIST)
            {
                out_vector->emplace_back(std::make_pair(l_it.key_, get_value(l_it.key_).value_or(0)));
            }
        }
    }
}
} // namespace s1ky
