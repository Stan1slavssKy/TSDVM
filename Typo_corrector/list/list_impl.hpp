#ifndef HASH_TABLE_LIST_LIST_IMPL_HPP_INCLUDED_
#define HASH_TABLE_LIST_LIST_IMPL_HPP_INCLUDED_

#include "list.hpp"

#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstring>
#include <iostream>

namespace s1ky {
template<typename key_t, typename data_t>
List<key_t, data_t>::List()
{}

template<typename key_t, typename data_t>
List<key_t, data_t>::List(key_t key, data_t data)
{
    front_ = new Node<key_t, data_t> {};
    assert(front_);

    front_->key_  = key;
    front_->data_ = data;
    size_         = 1;
    back_         = front_;
}

template<typename key_t, typename data_t>
List<key_t, data_t>::List(const List& other) : size_(other.size_)
{
    if (!empty())
    {
        front_ = new Node<key_t, data_t> {};
        assert(front_);

        Node<key_t, data_t>* cur_node       = front_;
        Node<key_t, data_t>* cur_other_node = other.front_;

        cur_node->key_  = cur_other_node->key_;
        cur_node->data_ = cur_other_node->data_;

        for (size_t i = 0; i < size_ - 1; i++)
        {
            cur_node->next_ = new Node<key_t, data_t> {};
            assert(cur_node->next_);

            cur_node       = cur_node->next_;
            cur_other_node = cur_other_node->next_;

            cur_node->key_  = cur_other_node->key_;
            cur_node->data_ = cur_other_node->data_;
        }
        back_ = cur_node;
    }
}

template<typename key_t, typename data_t>
List<key_t, data_t>::List(List&& other) noexcept : size_(other.size_), front_(other.front_), back_(other.back_)
{
    other.size_  = 0;
    other.front_ = nullptr;
    other.back_  = nullptr;
}

template<typename key_t, typename data_t>
List<key_t, data_t>::~List()
{
    delete_nodes();
}

//==========================================================================================================

template<typename key_t, typename data_t>
List<key_t, data_t>& List<key_t, data_t>::operator=(const List& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete_nodes();
    size_ = other.size_;

    if (!empty())
    {
        front_ = new Node<key_t, data_t> {};
        assert(front_);

        Node<key_t, data_t>* cur_node       = front_;
        Node<key_t, data_t>* cur_other_node = other.front_;

        cur_node->key_  = cur_other_node->key_;
        cur_node->data_ = cur_other_node->data_;

        for (size_t i = 0; i < size_ - 1; i++)
        {
            cur_node->next_ = new Node<key_t, data_t> {};
            assert(cur_node->next_);

            cur_node       = cur_node->next_;
            cur_other_node = cur_other_node->next_;

            cur_node->key_  = cur_other_node->key_;
            cur_node->data_ = cur_other_node->data_;
        }
        back_ = cur_node;
    }
    else
    {
        back_ = front_ = nullptr;
    }

    return *this;
}

template<typename key_t, typename data_t>
List<key_t, data_t>& List<key_t, data_t>::operator=(List&& other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    delete_nodes();

    size_  = other.size_;
    front_ = other.front_;
    back_  = other.back_;

    other.size_  = 0;
    other.front_ = nullptr;
    other.back_  = nullptr;

    return *this;
}

template<typename key_t, typename data_t>
bool List<key_t, data_t>::operator==(const List<key_t, data_t>& other) const
{
    if (this == &other)
    {
        return true;
    }
    if (empty() && other.empty())
    {
        return true;
    }
    if (size_ != other.size_)
    {
        return false;
    }

    Node<key_t, data_t>* cur_node       = front_;
    Node<key_t, data_t>* other_cur_node = other.front_;

    for (size_t i = 0; i < size_; i++)
    {
        if ((cur_node->data_ != other_cur_node->data_) && (cur_node->key_ != other_cur_node->key_))
        {
            return false;
        }

        cur_node       = cur_node->next_;
        other_cur_node = other_cur_node->next_;
    }

    return true;
}

template<typename key_t, typename data_t>
bool List<key_t, data_t>::operator!=(const List& other) const
{
    if (this == &other)
    {
        return false;
    }
    if (empty() && other.empty())
    {
        return false;
    }
    if (size_ != other.size_)
    {
        return true;
    }

    Node<key_t, data_t>* cur_node       = front_;
    Node<key_t, data_t>* other_cur_node = other.front_;

    for (size_t i = 0; i < size_; i++)
    {
        if ((cur_node->data_ != other_cur_node->data_) && (cur_node->key_ != other_cur_node->key_))
        {
            return true;
        }

        cur_node       = cur_node->next_;
        other_cur_node = other_cur_node->next_;
    }

    return false;
}

//==========================================================================================================

template<typename key_t, typename data_t>
bool List<key_t, data_t>::empty() const
{
    return size_ == 0;
}

template<typename key_t, typename data_t>
size_t List<key_t, data_t>::size() const
{
    return size_;
}

template<typename key_t, typename data_t>
data_t& List<key_t, data_t>::front()
{
    return front_->data_;
}

template<typename key_t, typename data_t>
data_t& List<key_t, data_t>::back()
{
    return back_->data_;
}

template<typename key_t, typename data_t>
const data_t& List<key_t, data_t>::front() const
{
    return front_->data_;
}

template<typename key_t, typename data_t>
const data_t& List<key_t, data_t>::back() const
{
    return back_->data_;
}

//==========================================================================================================

template<typename key_t, typename data_t>
Node<key_t, data_t>* List<key_t, data_t>::push(key_t key, data_t value)
{
    if (!empty())
    {
        back_->next_ = new Node<key_t, data_t> {};
        assert(back_->next_);

        back_ = back_->next_;

        back_->key_  = key;
        back_->data_ = value;
        ++size_;

        return nullptr;
    }

    back_ = front_ = new Node<key_t, data_t> {};
    assert(front_);

    back_->key_  = key;
    back_->data_ = value;
    ++size_;

    return front_;
}

template<typename key_t, typename data_t>
void List<key_t, data_t>::pop()
{
    if (!empty())
    {
        if (size_ == 1)
        {
            delete front_;
            front_ = back_ = nullptr;
        }
        else
        {
            Node<key_t, data_t>* temp = front_;
            front_                    = front_->next_;

            delete temp;
            temp = nullptr;
        }
        size_--;
    }
    else
    {
        std::cout << "pop error, stack is empty!" << std::endl;
    }
}

template<typename key_t, typename data_t>
void List<key_t, data_t>::swap(List* other)
{
    List<key_t, data_t> temp = std::move(*this);

    *this  = std::move(*other);
    *other = std::move(temp);
}

template<typename key_t, typename data_t>
void List<key_t, data_t>::delete_nodes()
{
    Node<key_t, data_t>* cur_node  = front_;
    Node<key_t, data_t>* next_node = nullptr;

    for (size_t i = 0; i < size_; ++i)
    {
        next_node = cur_node->next_;
        delete cur_node;
        cur_node = next_node;
    }
}

template<typename key_t, typename data_t>
Node<key_t, data_t>* List<key_t, data_t>::find_value(key_t key)
{
    Node<key_t, data_t>* current_elem = front_;

    for (size_t i = 0; i < size_; ++i)
    {
        if (current_elem->key_ == key)
        {
            return current_elem;
        }
        current_elem = current_elem->next_;
    }

    return nullptr;
}

template<typename key_t, typename data_t>
Node<key_t, data_t>* List<key_t, data_t>::delete_node(key_t key)
{
    Node<key_t, data_t>* current_elem = front_;
    Node<key_t, data_t>* prev_elem    = nullptr;

    for (size_t i = 0; i < size_; ++i)
    {
        if (current_elem->key_ == key)
        {
            if (prev_elem == nullptr)
            {
                front_ = current_elem->next_;

                if (front_ == nullptr)
                {
                    back_ = front_;
                }
            }
            else
            {
                prev_elem->next_ = current_elem->next_;
                if (prev_elem->next_ == nullptr)
                {
                    back_ = prev_elem;
                }
            }

            delete current_elem;
            --size_;
            break;
        }
        prev_elem    = current_elem;
        current_elem = current_elem->next_;
    }

    return front_;
}

template<typename key_t, typename data_t>
void List<key_t, data_t>::delete_invalid_node()
{
    Node<key_t, data_t>* current_elem = front_;
    Node<key_t, data_t>* prev_elem    = nullptr;

    for (size_t i = 0; i < size_; ++i)
    {
        bool is_invalid = false;

        if constexpr ((std::is_same<data_t, List<size_t, std::string>>::value == true) && (current_elem->data_.size() == 0))
        {
            is_invalid = true;
        }
        else if (!current_elem->data_)
        {
            is_invalid = true;
        }

        if (is_invalid)
        {
            if (prev_elem == nullptr)
            {
                front_ = current_elem->next_;

                if (front_ == nullptr)
                {
                    back_ = front_;
                }
            }
            else
            {
                prev_elem->next_ = current_elem->next_;
                if (prev_elem->next_ == nullptr)
                {
                    back_ = prev_elem;
                }
            }

            delete current_elem;
            --size_;
            break;
        }
        prev_elem    = current_elem;
        current_elem = current_elem->next_;
    }
}
} // namespace s1ky

#endif // HASH_TABLE_LIST_LIST_IMPL_HPP_INCLUDED_
