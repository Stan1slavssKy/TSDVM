#include "stack.hpp"
#include <cassert>
#include <cstring>

//----------------------------------------------------------------------------------------------

stack::stack (double capacity, double size): 
capacity_ (capacity), size_ (size)
{
    data_ = (double*) calloc (capacity_, sizeof (double));
    assert (data_);
}

stack::stack (const stack& other):
capacity_ (other.capacity_), size_ (other.size_)
{
    if (capacity_ >= 0)
    {
        data_ = (double*) realloc (data_, capacity_);
        assert (data_);
        memcpy (data_, other.data_, size_);
    }
    else
    {
        error_ = NEGATIVE_CAPACITY;
    }
}

stack::stack (stack&& other)
{

}

stack::~stack ()
{
    free (data_);
}

//----------------------------------------------------------------------------------------------