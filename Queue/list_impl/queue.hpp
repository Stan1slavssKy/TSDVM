#ifndef _QUEUE_LIST_IMPL_QUEUE_HPP
#define _QUEUE_LIST_IMPL_QUEUE_HPP

#include <cstdlib>

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

    Queue<T>& operator=(const Queue& other);
    Queue<T>& operator=(Queue&& other) noexcept;

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;

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
    struct Node
    {
        T     data_ = 0;
        Node* next_ = nullptr;
    };

    size_t size_  = 0;
    Node*  front_ = nullptr;
    Node*  back_  = nullptr;

    void delete_nodes();
};
} // namespace s1ky

#endif // _QUEUE_LIST_IMPL_QUEUE_HPP