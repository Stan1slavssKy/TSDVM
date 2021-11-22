#ifndef _QUEUE_LIST_IMPL_QUEUE_IMPL_HPP_INCLUDED
#define _QUEUE_LIST_IMPL_QUEUE_IMPL_HPP_INCLUDED

#include "queue.hpp"

#include <iostream>
#include <cassert>
#include <cstring>

namespace s1ky 
{
template<typename T>
Queue<T>::Queue()
{
    front_ = new Node{};
    assert(front_);

    size_ = 1;
}

template<typename T>
Queue<T>::Queue(T data)
{
    front_ = new Node {};
    assert(front_);

    front_->data_ = data;
    size_        = 1;
}

template<typename T>
Queue<T>::Queue(const Queue& other) : size_(other.size_)
{
    if(!empty())
    {
        front_ = new Node {};
        assert(front_);

        Node* cur_node       = front_;
        Node* cur_other_node = other.front_;
        
        cur_node->data_ = cur_other_node->data_;

        for(size_t i = 0; i < size_ - 1; i++)
        {
            cur_node -> next = new Node {};
            assert(cur_node -> next_);
            
            cur_node       = cur_node -> next_;
            cur_other_node = cur_other_node -> next_;

            cur_node->data_ = cur_other_node->data_;
        }
        back_ = cur_node;
    }
}

template<typename T>
Queue<T>::Queue(Queue&& other) noexcept : size_(other.size_), front_(other.front_), back_(other.back_)
{
    front_ = nullptr;
    back_  = nullptr;
}

template<typename T>
Queue<T>::~Queue()
{
    delete front_;
}

//==========================================================================================================
/*
template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other)
{
    if(*this = &other) return *this;

    size_ = other.size_;
    delete_nodes();

    if(!empty())
    {
        front_ = new Node {};
        assert(front_);

        Node* cur_node       = front_;
        Node* cur_other_node = other.front_;
        
        memcpy(cur_node->data_, cur_other_node->data_, sizeof(T));

        for(size_t i = 0; i < size_ - 1; i++)
        {
            cur_node -> next = new Node {};
            assert(cur_node -> next_);
            
            cur_node       = cur_node -> next_;
            cur_other_node = cur_other_node -> next_;

            memcpy(cur_node->data_, cur_other_node->data_, sizeof(T));
        }
        back_ = cur_node;
    }
}
*/
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
Queue<T>& Queue<T>::front()
{
    return front_;
}

template<typename T>
Queue<T>& Queue<T>::back()
{
    return back_;
}

template<typename T>
const Queue<T>& Queue<T>::front() const
{
    return front_;
}

template<typename T>
const Queue<T>& Queue<T>::back() const
{
    return back_;
}

//==========================================================================================================

template<typename T>
void Queue<T>::push(T value)
{
    if(!empty())
    {
        back_->next_ = new Node {};
        assert(back_->next_);

        back_ = back_->next_;
        back_->data_ = value;

        size_++;
    }
    else
    {
        std::cout << "push error, stack is empty!" << std::endl;
    }
}

template<typename T>
void Queue<T>::pop()
{
    if(!empty())
    {
        if(size_ == 1)
        {
            delete front_;
            front_ = back_ = nullptr;
        }

        Node* temp = front_;
        front_ = front_->next_;
        
        delete temp;
        temp = nullptr;
        
        size_--;
    }
    else
    {
        std::cout << "pop error, stack is empty!" << std::endl;
    }
}

} //namespace s1ky

#endif // _QUEUE_LIST_IMPL_QUEUE_IMPL_HPP_INCLUDED
