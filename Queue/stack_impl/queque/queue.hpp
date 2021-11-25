#ifndef _STACK_IMPL_QUEUE_QUEUE_HPP
#define _STACK_IMPL_QUEUE_QUEUE_HPP

#include "../stack/stack_impl.hpp"

namespace s1ky {
template<typename T>
class Queue
{
public:
    Queue();
    Queue~();

private:
    size_ = 0;
    Stack<T> input_stack  = nullptr;
    Stack<T> output_stack = nullptr;
};
} //namespace s1ky

#endif // _STACK_IMPL_QUEUE_QUEUE_HPP