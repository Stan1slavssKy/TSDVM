#ifndef STACK_STACK_HPP_INCLUDED
#define STACK_STACK_HPP_INCLUDED   

//----------------------------------------------------------------------------------------------

#include <cstdlib> 

//----------------------------------------------------------------------------------------------

template <typename T>
class stack
{
    public:
        stack ();
        stack (T* data, size_t size);
        stack (const stack& other);
        stack (stack&& other);

        ~stack ();

        stack& operator= (const stack& other);
        stack& operator= (stack&& other);
        
        bool operator==(const stack& other) const;
        bool operator!=(const stack& other) const;

        void push (const T value);
        void pop ();
        void print () const;
        bool is_empty () const;
        
        T& top (); 
        const T& top () const; 
        size_t size () const;

    private:
        const size_t init_capacity_  = 16;
        const T stack_increase_ = 1.5;

        size_t  capacity_;
        size_t  size_;
        T* data_;

        void expands_capacity ();
};

//----------------------------------------------------------------------------------------------

#endif //STACK_STACK_HPP_INCLUDED