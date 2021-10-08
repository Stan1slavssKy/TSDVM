#ifndef STACK_STACK_H_INCLUDED
#define STACK_STACK_H_INCLUDED    

//----------------------------------------------------------------------------------------------

#include <cstdlib> // for size_t

//----------------------------------------------------------------------------------------------

enum stack_error
{
    NEGATIVE_CAPACITY = -1,
    
};

//----------------------------------------------------------------------------------------------

class stack
{
    public:
        stack ();
        stack (double* data, size_t size);
        stack (const stack& other);
        stack (stack&& other);

        ~stack ();

        stack& operator= (const stack& other);
        stack& operator= (stack&& other);

        void push  (const double value);
        void pop   ();
        void print ();
        void expands_capacity ();

    private:
        const size_t init_capacity_  = 16;
        const double stack_increase_ = 1.5;

        size_t  capacity_;
        size_t  size_;
        double* data_;

};

//----------------------------------------------------------------------------------------------

#endif // STACK_STACK_H_INCLUDED 