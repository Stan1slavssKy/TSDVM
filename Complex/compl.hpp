#ifndef COMPLEX_HPP_INCLUDED
#define COMPLEX_HPP_INCLUDED

//=======================================================

#include <iostream>

//=======================================================

class complex
{
    private:
        double Re_;
        double Im_;

    public:
        complex ();
        complex (double Re, double Im);
        ~complex () {};

        double abs ();
        void   print ();
};

//=======================================================

#endif