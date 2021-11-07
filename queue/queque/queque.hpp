#ifndef QUEQUE_HPP_INCLUDED
#define QUEQUE_HPP_INCLUDED

#include <cstdlib>

namespace s1ky 
{
template<typename T>
class queque
{
public:
    queque
    queque~();

    const size_t INIT_CAPACITY     = 16;
    const double CAPACITY_INCREASE = 1.5;

private:
    size_t capacity_;
    size_t size_;
    T*     data_;

    void expand_capacity ();
};
} // namespace s1ky

#endif