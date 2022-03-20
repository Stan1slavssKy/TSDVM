#include "dictionary.hpp"

#include <algorithm>
#include <vector>

namespace s1ky {
std::string Dictionary::find_similar_word(const std::string& word) const
{
    for (auto& ll_it : *iteration_list_)
    {
        for (auto& l_it : *ll_it.data_)
        {
            size_t lev_dist = lev_distance_calculation(word, (l_it.key_));

            if (lev_dist <= ACCEPTABLE_LEV_DIST)
            {
                return l_it.key_;
            }
        }
    }

    return "\0"; // NOLINT
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
