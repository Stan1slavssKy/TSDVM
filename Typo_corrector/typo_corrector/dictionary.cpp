#include "dictionary.hpp"

namespace s1ky {
std::string Dictionary::find_similar_word(std::string word)
{
    //List<std::string, size_t> cur_llnode = iteration_list_->front(); //I dont understand why it isnt compile
    
    for (auto ll_it = iteration_list_->begin(); ll_it != iteration_list_->end(); ++ll_it)
    {
        Node<std::string, size_t>* found_node = ll_it->find_value(word);
        
        if (found_node != nullptr)
        {
            return found_node->key_;
        }

        for (auto l_it = ll_it->begin(); l_it != ll_it->end(); ++l_it)
        {
            size_t lev_dist = lev_distance_calculation(word, (l_it->key_).c_str());
            if (lev_dist == 1)
            {
                return l_it->key_;
            }
        }

    }
    
    return word;
}

size_t lev_distance_calculation(const char* lhs, const char* rhs)
{
    return 0;
}
} // namespace s1ky