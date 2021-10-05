#ifndef INCLUDES_STACK_H_INCLUDED
#define INCLUDES_STACK_H_INCLUDED    

//----------------------------------------------------------------------------------------------

#include <cstdlib> // for size_t

//----------------------------------------------------------------------------------------------

const size_t INIT_CAPACITY = 16;
const size_t STACK_INCREASE = 2;

enum stack_error
{
    NEGATIVE_CAPACITY = -1,
    
};

//----------------------------------------------------------------------------------------------

class stack
{
        size_t  capacity_; // max number of elements
        size_t  size_;     // number of elements
        double* data_;     // data
        int     error_;

    public:
        stack  ();
        stack  (double capacity, double size);
        stack  (const stack& other);
        stack  (stack&& other);
        ~stack ();

        stack& operator= (const stack& other);
        stack& operator= (stack&& other);

        void push  (const double value);
        void pop   ();
        void print ();
};

//----------------------------------------------------------------------------------------------

#endif