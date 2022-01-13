#ifndef _QUEUE_LIST_IMPL_QUEUE_IMPL_HPP_INCLUDED
#define _QUEUE_LIST_IMPL_QUEUE_IMPL_HPP_INCLUDED

#include "queue.hpp"

#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstring>
#include <iostream>

namespace s1ky {
namespace list_queue {
template<typename T>
Queue<T>::Queue()
{}

template<typename T>
Queue<T>::Queue(T data)
{
    front_ = new Node {};
    assert(front_);

    front_->data_ = data;
    size_         = 1;
    back_         = front_;
}

template<typename T>
Queue<T>::Queue(const Queue& other) : size_(other.size_)
{
    if (!empty())
    {
        front_ = new Node {};
        assert(front_);

        Node* cur_node       = front_;
        Node* cur_other_node = other.front_;

        cur_node->data_ = cur_other_node->data_;

        for (size_t i = 0; i < size_ - 1; i++)
        {
            cur_node->next_ = new Node {};
            assert(cur_node->next_);

            cur_node       = cur_node->next_;
            cur_other_node = cur_other_node->next_;

            cur_node->data_ = cur_other_node->data_;
        }
        back_ = cur_node;
    }
}

template<typename T>
Queue<T>::Queue(Queue&& other) noexcept : size_(other.size_), front_(other.front_), back_(other.back_)
{
    other.size_  = 0;
    other.front_ = nullptr;
    other.back_  = nullptr;
}

template<typename T>
Queue<T>::~Queue()
{
    delete_nodes();
}

//==========================================================================================================

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete_nodes();
    size_ = other.size_;

    if (!empty())
    {
        front_ = new Node {};
        assert(front_);

        Node* cur_node       = front_;
        Node* cur_other_node = other.front_;

        cur_node->data_ = cur_other_node->data_;

        for (size_t i = 0; i < size_ - 1; i++)
        {
            cur_node->next_ = new Node {};
            assert(cur_node->next_);

            cur_node       = cur_node->next_;
            cur_other_node = cur_other_node->next_;

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

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept
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

template<typename T>
bool Queue<T>::operator==(const Queue& other) const
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

    Node* cur_node       = front_;
    Node* other_cur_node = other.front_;

    for (size_t i = 0; i < size_; i++)
    {
        if (cur_node->data_ != other_cur_node->data_)
        {
            return false;
        }

        cur_node       = cur_node->next_;
        other_cur_node = other_cur_node->next_;
    }

    return true;
}

template<typename T>
bool Queue<T>::operator!=(const Queue& other) const
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

    Node* cur_node       = front_;
    Node* other_cur_node = other.front_;

    for (size_t i = 0; i < size_; i++)
    {
        if (cur_node->data_ != other_cur_node->data_)
        {
            return true;
        }

        cur_node       = cur_node->next_;
        other_cur_node = other_cur_node->next_;
    }

    return false;
}

//==========================================================================================================

template<typename T>
bool Queue<T>::empty() const
{
    return size_ == 0;
}

template<typename T>
size_t Queue<T>::size() const
{
    return size_;
}

template<typename T>
T& Queue<T>::front()
{
    return front_->data_;
}

template<typename T>
T& Queue<T>::back()
{
    return back_->data_;
}

template<typename T>
const T& Queue<T>::front() const
{
    return front_->data_;
}

template<typename T>
const T& Queue<T>::back() const
{
    return back_->data_;
}

//==========================================================================================================

template<typename T>
void Queue<T>::push(T value)
{
    if (!empty())
    {
        back_->next_ = new Node {};
        assert(back_->next_);

        back_ = back_->next_;
    }
    else
    {
        back_ = front_ = new Node {};
        assert(front_);
    }
    back_->data_ = value;
    size_++;
}

template<typename T>
void Queue<T>::pop()
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
            Node* temp = front_;
            front_     = front_->next_;

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

template<typename T>
void Queue<T>::swap(Queue* other)
{
    Queue<T> temp = std::move(*this);

    *this  = std::move(*other);
    *other = std::move(temp);
}

template<typename T>
void Queue<T>::delete_nodes()
{
    Node* cur_node  = front_;
    Node* next_node = nullptr;

    for (size_t i = 0; i < size_; i++)
    {
        next_node = cur_node->next_;
        delete cur_node;
        cur_node = next_node;
    }
}

template<typename T>
Queue<T>& Queue<T>::find_value(const T value) const
{
    Queue<T>* current_elem = front_;

    for (int i = 0; i < size_; ++i)
    {
        if (current_elem.data_ == value)
        {
            return current_elem;
        }
        current_elem = current_elem.next_;
    }

    return nullptr;
}

} // namespace list_queue
} // namespace s1ky

#endif // _QUEUE_LIST_IMPL_QUEUE_IMPL_HPP_INCLUDED
