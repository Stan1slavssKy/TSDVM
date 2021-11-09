#ifndef STACK_STACK_HPP_INCLUDED
#define STACK_STACK_HPP_INCLUDED

#include <cstdlib>

namespace s1ky {
template<typename T>
class Stack
{
public:
    Stack();
    Stack(T* data, size_t size);
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;

    ~Stack();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

    void push(T value);
    void pop();
    void print() const;
    bool is_empty() const;

    T&       top();
    const T& top() const;
    size_t   size() const;

    const size_t INIT_CAPACITY  = 16;
    const double STACK_INCREASE = 1.5;

private:
    size_t capacity_ = 0;
    size_t size_     = 0;
    T*     data_     = nullptr;

    void expands_capacity();
};

template<>
class Stack<bool>
{
public:
    Stack();
    Stack(unsigned char* data, size_t size);
    Stack(const Stack& other);
    Stack(Stack&& other) noexcept;

    ~Stack();

    Stack& operator=(const Stack& other);
    Stack& operator=(Stack&& other) noexcept;

    bool operator==(const Stack& other) const;
    bool operator!=(const Stack& other) const;

    void push(bool bool_value);
    void print() const;
    void pop();
    bool is_empty() const;
    bool top() const;

    size_t size() const;

    const size_t INIT_CAPACITY  = 2;
    const size_t STACK_INCREASE = 2;

private:
    size_t         capacity_ = 0;
    size_t         size_     = 0;
    unsigned char* data_     = nullptr;

    void expands_capacity();
};

} // namespace s1ky

#endif // STACK_STACK_HPP_INCLUDED
