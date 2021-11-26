#ifndef _STACK_IMPL_QUEUE_QUEUE_HPP
#define _STACK_IMPL_QUEUE_QUEUE_HPP

#include "../stack/stack_impl.hpp"

namespace s1ky {
template<typename T>
class Queue
{
public:
    Queue();
    Queue(T data);
    Queue(const Queue& other);
    Queue(Queue&& other) noexcept;
    ~Queue();

    bool operator==(const Queue<T>& other) const;
    bool operator!=(const Queue& other) const;

    Queue<T>& operator=(const Queue& other);
    Queue<T>& operator=(Queue&& other) noexcept;

    bool   empty() const;
    size_t size() const;

    T& front();
    T& back();

    const T& front() const;
    const T& back() const;

    void push(T value);
    void pop();
    void swap(Queue* other);

private:
    size_t size_;
    T*     back_ = nullptr;

    Stack<T> input_stack_;
    Stack<T> output_stack_;

    void move_from_input_stack();
};
} // namespace s1ky

#endif // _STACK_IMPL_QUEUE_QUEUE_HPP