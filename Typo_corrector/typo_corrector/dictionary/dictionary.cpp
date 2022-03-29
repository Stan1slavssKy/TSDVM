#include "dictionary.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <vector>
#include <functional>

namespace s1ky {
Dictionary::Dictionary()
{
    threads_number_ = std::thread::hardware_concurrency();
}

Dictionary::Dictionary(size_t threads_number) : threads_number_(threads_number)
{}

Dictionary::Dictionary(Dictionary&& other) noexcept :
    threads_number_(other.threads_number_), nmb_iterations_per_thread_(other.nmb_iterations_per_thread_),
    nmb_iterations_for_last_thread_(other.nmb_iterations_for_last_thread_)
{
    std::swap(threads_, other.threads_);
}

Dictionary& Dictionary::operator=(Dictionary&& other) noexcept
{
    if (this == &other)
        return *this;

    std::swap(threads_, other.threads_);

    threads_number_                 = other.threads_number_;
    nmb_iterations_per_thread_      = other.nmb_iterations_per_thread_;
    nmb_iterations_for_last_thread_ = other.nmb_iterations_for_last_thread_;

    return *this;
}

//=========================================================================================================================

std::vector<std::pair<std::string, size_t>> Dictionary::get_similar_word_thread(const std::string& token)
{
    if (threads_number_ <= 1)
        return find_similar_word(token);

    nmb_iterations_per_thread_ = valid_nodes_.size() / threads_number_;
    nmb_iterations_for_last_thread_ = nmb_iterations_per_thread_ + valid_nodes_.size() % threads_number_;

    auto* suitable_words = new std::vector<std::string>[threads_number_];

    std::vector<std::pair<std::string, size_t>> output;

    call_threads_(token, suitable_words);
    join_threads_();
    make_output_words_(suitable_words, &output);

    delete[] suitable_words;
    threads_.clear();

    return output;
}

void Dictionary::call_threads_(const std::string& token, std::vector<std::string>* suitable_words)
{
    for (size_t i = 0; i < threads_number_; ++i)
    {
        size_t beg_pos = nmb_iterations_per_thread_ * i;
        size_t end_pos = beg_pos + nmb_iterations_per_thread_;

        if (i == (threads_number_ - 1))
        {
            end_pos = beg_pos + nmb_iterations_for_last_thread_;
        }
        threads_.emplace_back(
            std::thread(find_similar_word_thread, std::ref(valid_nodes_), &suitable_words[i], std::ref(token), beg_pos, end_pos));
    }
}

void Dictionary::join_threads_()
{
    for (size_t i = 0; i < threads_number_; ++i) 
    {
        if (threads_[i].joinable())
        {
            threads_[i].join();
        }        
    }
}

void Dictionary::make_output_words_(std::vector<std::string>* suitable_words, 
                                    std::vector<std::pair<std::string, size_t>>* output)
{
    for (size_t i = 0; i < threads_number_; ++i)
    {
        for (const auto& vec_it : suitable_words[i])
        {
            output->emplace_back(std::make_pair(vec_it, get_value(vec_it).value_or(0)));
        }
    }
}

void Dictionary::find_similar_word_thread(const std::vector<Node<std::string, size_t>*>& input_vector,
                                         std::vector<std::string>* out_vector,
                                         const std::string& word, size_t beg_pos, size_t end_pos) //NOLINT
{
    for (size_t i = beg_pos; i < end_pos; ++i)
    {
        size_t lev_dist = Dictionary::lev_distance_calculation(word, input_vector[i]->key_);

        if (lev_dist <= Dictionary::ACCEPTABLE_LEV_DIST)
        {
            out_vector->emplace_back(input_vector[i]->key_);
            return;
        }
    }
}

//=========================================================================================================================

std::vector<std::pair<std::string, size_t>> Dictionary::find_similar_word(const std::string& word) const
{
    std::vector<std::pair<std::string, size_t>> suitable_words;

    for (auto* it : valid_nodes_)
    {
        size_t lev_dist = lev_distance_calculation(word, it->key_);

        if (lev_dist <= ACCEPTABLE_LEV_DIST)
        {
            suitable_words.emplace_back(std::make_pair(it->key_, get_value(it->key_).value_or(0)));
        }
    }

    return suitable_words;
}

size_t Dictionary::lev_distance_calculation(const std::string& lhs, const std::string& rhs) // NOLINT
{
    if (lhs.size() > rhs.size())
    {
        return lev_distance_calculation(rhs, lhs);
    }

    const size_t min_size = lhs.size();
    const size_t max_size = rhs.size();

    std::vector<size_t> lev_dist(min_size + 1);

    for (size_t i = 0; i <= min_size; ++i) { lev_dist[i] = i; }

    for (size_t j = 1; j <= max_size; ++j)
    {
        size_t previous_diagonal      = lev_dist[0];
        size_t previous_diagonal_save = 0;

        ++lev_dist[0];

        for (size_t i = 1; i <= min_size; ++i)
        {
            previous_diagonal_save = lev_dist[i];

            if (lhs[i - 1] == rhs[j - 1])
            {
                lev_dist[i] = previous_diagonal;
            }
            else
            {
                lev_dist[i] = std::min(std::min(lev_dist[i - 1], lev_dist[i]), previous_diagonal) + 1;
            }
            previous_diagonal = previous_diagonal_save;
        }
    }
    return lev_dist[min_size];
}
} // namespace s1ky
