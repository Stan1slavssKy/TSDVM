#ifndef _STACK_IMPL_QUEUE_QUEUE_IMPL_HPP
#define _STACK_IMPL_QUEUE_QUEUE_IMPL_HPP

#include "queue.hpp"

namespace s1ky {

template<typename T>
Queue<T>::Queue() : size_(0)
{}

template<typename T>
Queue<T>::Queue(T data) : size_(1), output_stack_(&data, 1)
{}

template<typename T>
Queue<T>::Queue(const Queue& other) :
    size_(other.size_), input_stack_(other.input_stack_), output_stack_(other.output_stack_)
{}

template<typename T>
Queue<T>::Queue(Queue&& other) noexcept
{
    size_         = other.size_;
    input_stack_  = std::move(other.input_stack_);
    output_stack_ = std::move(other.output_stack_);
}

template<typename T>
Queue<T>::~Queue()
{}

//==========================================================================================================

template<typename T>
bool Queue<T>::operator==(const Queue<T>& other) const
{
    if (this == &other)
    {
        return true;
    }

    return (input_stack_ == other.input_stack_) && (output_stack_ == other.output_stack_);
}

template<typename T>
bool Queue<T>::operator!=(const Queue& other) const
{
    if (this == &other)
    {
        return false;
    }

    return (input_stack_ != other.input_stack_) || (output_stack_ != other.output_stack_);
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& other)
{
    if (this == &other)
    {
        return *this;
    }

    size_         = other.size_;
    input_stack_  = other.input_stack_;
    output_stack_ = other.output_stack_;

    return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& other) noexcept
{
    size_         = other.size_;
    input_stack_  = std::move(other.input_stack_);
    output_stack_ = std::move(other.output_stack_);

    return *this;
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
    if (output_stack_.is_empty())
    {
        move_from_input_stack();
    }

    return output_stack_.top();
}

template<typename T>
const T& Queue<T>::front() const
{
    if (output_stack_.is_empty())
    {
        move_from_input_stack();
    }

    return output_stack_.top();
}

template<typename T>
T& Queue<T>::back()
{
    return *back_;
}

template<typename T>
const T& Queue<T>::back() const
{
    return *back_;
}

//==========================================================================================================

template<typename T>
void Queue<T>::move_from_input_stack()
{
    T top_input_value = 0;

    while (!input_stack_.is_empty())
    {
        top_input_value = input_stack_.top();
        output_stack_.push(top_input_value);
        input_stack_.pop();
    }
}

template<typename T>
void Queue<T>::push(T value)
{
    input_stack_.push(value);
    size_++;

    back_ = &input_stack_.top();
}

template<typename T>
void Queue<T>::pop()
{
    if (output_stack_.is_empty())
    {
        move_from_input_stack();

        if (output_stack_.is_empty())
        {
            std::cout << "pop error, queue is empty" << std::endl;
            return;
        }
    }

    output_stack_.pop();
    size_--;
}

template<typename T>
void Queue<T>::swap(Queue* other)
{
    Queue<T> temp = std::move(*this);
    *this         = std::move(*other);
    *other        = std::move(temp);
}
} // namespace s1ky

#endif //_STACK_IMPL_QUEUE_QUEUE_IMPL_HPP