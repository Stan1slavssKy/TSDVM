#ifndef STACK_STACK_HPP_INCLUDED
#define STACK_STACK_HPP_INCLUDED   

#include <cstdlib> 

namespace s1ky
{  
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

        void push (T value);
        void pop ();
        void print () const;
        bool is_empty () const;
        
        T& top (); 
        const T& top () const; 
        size_t size () const;

        const size_t INIT_CAPACITY  = 16;
        const double STACK_INCREASE = 1.5;

    private:
        size_t capacity_;
        size_t size_;
        T* data_;
                    
        void expands_capacity ();
};

template <>
class stack<bool>
{
    public:
        stack ();
        stack (unsigned char* data, size_t size);
        stack (const stack& other);
        stack (stack&& other);

        ~stack ();

        stack& operator= (const stack& other);
        stack& operator= (stack&& other);

        bool operator== (const stack& other) const;
        bool operator!= (const stack& other) const;

        void push (bool bool_value);
        void print () const;
        void pop ();
        bool is_empty () const;
        bool top () const;

        size_t size () const;

        const size_t INIT_CAPACITY  = 2;
        const size_t STACK_INCREASE = 2;

    private:
        size_t capacity_;
        size_t size_;
        unsigned char* data_;
                    
        void expands_capacity ();
};

}//namespace s1ky

#endif //STACK_STACK_HPP_INCLUDED
