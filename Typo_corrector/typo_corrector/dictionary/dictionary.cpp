#include "dictionary.hpp"

#include <algorithm>
#include <cstring>
#include <functional>
#include <iostream>
#include <vector>

namespace s1ky {
Dictionary::Dictionary()
{
    threads_number = std::thread::hardware_concurrency();
}

Dictionary::Dictionary(size_t threads_number) : threads_number(threads_number) {}

Dictionary::Dictionary(Dictionary&& other) noexcept :
    threads_number(other.threads_number), nmb_iterations_per_thread(other.nmb_iterations_per_thread),
    nmb_iterations_for_last_thread(other.nmb_iterations_for_last_thread)
{
    std::swap(threads_, other.threads_);
}

Dictionary& Dictionary::operator=(Dictionary&& other) noexcept
{
    if (this == &other)
        return *this;

    std::swap(threads_, other.threads_);

    threads_number                 = other.threads_number;
    nmb_iterations_per_thread      = other.nmb_iterations_per_thread;
    nmb_iterations_for_last_thread = other.nmb_iterations_for_last_thread;

    return *this;
}

//=========================================================================================================================

std::string* Dictionary::get_similar_word_thread(const std::string& token)
{
    if (threads_number <= 1)
        return find_similar_word(token);

    nmb_iterations_per_thread      = valid_nodes_.size() / threads_number;
    nmb_iterations_for_last_thread = nmb_iterations_per_thread + valid_nodes_.size() % threads_number;

    auto* suitable_words = new std::vector<std::pair<std::string*, size_t>>[threads_number];

    std::vector<std::pair<std::string*, size_t>> out_pair;

    call_threads(token, suitable_words);
    join_threads(suitable_words, &out_pair);
    threads_.clear();

    delete[] suitable_words;

    if (out_pair.empty())
        return nullptr;

    return find_best_word(&out_pair);
}

void Dictionary::call_threads(const std::string& token, std::vector<std::pair<std::string*, size_t>>* suitable_words)
{
    for (size_t i = 0; i < threads_number; ++i)
    {
        size_t beg_pos = nmb_iterations_per_thread * i;
        size_t end_pos = beg_pos + nmb_iterations_per_thread;

        if (i == (threads_number - 1))
        {
            end_pos = beg_pos + nmb_iterations_for_last_thread;
        }

        threads_.emplace_back(std::thread(&Dictionary::find_similar_word_thread, this, &suitable_words[i],
                                          std::ref(token), beg_pos, end_pos));
    }
}

void Dictionary::join_threads(std::vector<std::pair<std::string*, size_t>>* suitable_words, // NOLINT
                              std::vector<std::pair<std::string*, size_t>>* out_pair)       // NOLINT
{
    for (size_t i = 0; i < threads_number; ++i)
    {
        if (threads_[i].joinable())
        {
            threads_[i].join();
        }
        for (auto& vec_it : suitable_words[i]) { out_pair->emplace_back(vec_it); }
    }
}

void Dictionary::find_similar_word_thread(std::vector<std::pair<std::string*, size_t>>* out_pairs,
                                          const std::string& word, size_t beg_pos, size_t end_pos) // NOLINT
{
    std::vector<std::pair<std::string*, size_t>> suitable_words;

    for (size_t i = beg_pos; i < end_pos; ++i)
    {
        size_t lev_dist = Dictionary::lev_distance_calculation(word, valid_nodes_[i]->key_);

        if (lev_dist <= Dictionary::ACCEPTABLE_LEV_DIST)
        {
            suitable_words.emplace_back(
                std::make_pair(&(valid_nodes_[i]->key_), get_value(valid_nodes_[i]->key_).value_or(0)));
        }
    }

    std::string* best_word = find_best_word(&suitable_words);
    if (best_word != nullptr)
        out_pairs->emplace_back(std::make_pair(best_word, get_value(*best_word).value_or(0)));
}

std::string* Dictionary::find_best_word(std::vector<std::pair<std::string*, size_t>>* suitable_words_pair)
{
    size_t cur_freq  = 0;
    size_t prev_freq = 0;

    std::string* best_word = nullptr;

    for (auto& it : *suitable_words_pair)
    {
        cur_freq = std::get<1>(it);
        if (cur_freq > prev_freq && cur_freq >= MIN_WORD_REPLACE_FREQ)
            best_word = std::get<0>(it);

        prev_freq = cur_freq;
    }

    return best_word;
}

//=========================================================================================================================

std::string* Dictionary::find_similar_word(const std::string& word) const
{
    std::vector<std::pair<std::string*, size_t>> suitable_words;

    for (auto* it : valid_nodes_)
    {
        size_t lev_dist = lev_distance_calculation(word, it->key_);

        if (lev_dist <= ACCEPTABLE_LEV_DIST)
        {
            suitable_words.emplace_back(std::make_pair(&(it->key_), get_value(it->key_).value_or(0)));
        }
    }

    if (suitable_words.empty())
        return nullptr;

    return find_best_word(&suitable_words);
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
