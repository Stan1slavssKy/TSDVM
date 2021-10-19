#ifndef STACK_STACK_BOOL_IMPL_HPP_INCLUDED
#define STACK_STACK_BOOL_IMPL_HPP_INCLUDED

//----------------------------------------------------------------------------------------------

namespace s1ky
{  

//----------------------------------------------------------------------------------------------

template <> stack<bool>::stack ():
    capacity_(init_capacity), size_(0)
{
    data_ = new bool[capacity_];
    assert (data_);
}

template <> stack<bool>::stack (bool* data, size_t size): 
    data_(data), size_ (size), capacity_(capacity_)
{
}

template <> stack<bool>::stack (const stack& other):
    capacity_ (other.capacity_), size_ (other.size_)
{
    delete[] data_;
    new bool[capacity_];

    assert (data_);
    memcpy (data_, other.data_, size_);
}

template <> stack<bool>::stack (stack&& other):
    capacity_(other.capacity_), size_(other.size_), data_(other.data_) 
{   
    other.data_ = nullptr;
}

template <> stack<bool>::~stack ()
{
    delete[] data_;
}

//----------------------------------------------------------------------------------------------

template <> stack<bool>& stack<bool>::operator= (const stack& other) 
{
    if (this == &other) return *this;

    delete[] data_;
    
    size_ = other.size_;
    capacity_ = other.capacity_;

    data_ = new bool[capacity_];
    assert (data_);
    
    memcpy(data_, other.data_, size_ * sizeof(bool));
    
    return *this;
}

template <> stack<bool>& stack<bool>::operator= (stack&& other)
{
    if (this == &other) return *this;

    free (data_);

    data_ = other.data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    
    other.data_ = nullptr;
    
    return *this;
}

template <> bool stack<bool>::operator==(const stack& other) const
{
    if (size_ != other.size_)
    {
        return false;
    }
    if (capacity_ != other.capacity_)
    {
        return false;
    }
    if (memcmp(data_, other.data_, size_ * sizeof (bool)))
    {
        return false;
    }
    return true;
}

template <> bool stack<bool>::operator!=(const stack& other) const
{
    if (size_ != other.size_)
    {
        return true;
    }
    if (capacity_ != other.capacity_)
    {
        return true;
    }
    if (memcmp(data_, other.data_, size_ * sizeof (bool)))
    {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------
 
template <> void stack<bool>::push (const bool value)
{
    if (size_ == capacity_)
    {
        expands_capacity ();
    }

    data_[size_++] = value;
}

template <> void stack<bool>::pop ()
{
    if (!is_empty())
    {
        data_[--size_] = 0;
    }
}

template <> void stack<bool>::print () const
{
    for (int i = 0; i < size_; i++)
    {
        std::cout << data_[i] << std::endl;
    }
}

template <> void stack<bool>::expands_capacity ()
{
    capacity_ = capacity_++;

    bool* temp = new bool[capacity_];
    assert (temp);

    memcpy(temp, data_, size_ * sizeof(bool));

    delete[] data_;
    data_ = temp;
}

template <> bool stack<bool>::is_empty () const
{
    return size_ == 0;
}

template <> bool& stack<bool>::top ()
{
    if (is_empty())
    {
        std::cout << "stack is empty, cant return top" << std::endl;
        return data_[0];
    }
    else
    {
        return data_[size_ - 1];
    }
}

template <> const bool& stack<bool>::top () const
{
    if (is_empty())
    {
        std::cout << "stack is empty, cant return top" << std::endl;
        return data_[0];
    }
    else
    {
        return data_[size_ - 1];
    }
}

template <> size_t stack<bool>::size () const
{
    return size_;
}

}//namespace s1ky

//----------------------------------------------------------------------------------------------

#endif //STACK_STACK_BOOL_IMPL_HPP_INCLUDED