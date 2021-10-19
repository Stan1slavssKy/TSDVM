#ifndef STACK_STACK_HPP_INCLUDED
#define STACK_STACK_HPP_INCLUDED   

//===========================================================================================

#include <cstdlib> 

//===========================================================================================

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

            void push (const T value);
            void pop ();
            void print () const;
            bool is_empty () const;
            
            T& top (); 
            const T& top () const; 
            size_t size () const;

            const size_t init_capacity  = 16;
            const double stack_increase = 1.5;

        private:
            size_t capacity_;
            size_t size_;
            T* data_;
                        
            void expands_capacity ();
    };
}//namespace s1ky

//===========================================================================================

#include "stack_impl.hpp"
#include "stack_bool_impl.hpp"

//===========================================================================================

#endif //STACK_STACK_HPP_INCLUDED
