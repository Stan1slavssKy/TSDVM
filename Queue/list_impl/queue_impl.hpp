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
Queue<T>::Queue(T* data)
{
    front_ = new Node {};
    assert(front_);

    front_->data_ = data;
    size_        = 1;
}

template<typename T>
Queue<T>::Queue(const Queue& other) : size_(other.size_)
{
    if(size_ != 0)
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

template<typename T>
Queue<T>::~Queue()
{
    delete front_;
}
} //namespace s1ky

#endif // _QUEUE_LIST_IMPL_QUEUE_IMPL_HPP_INCLUDED
