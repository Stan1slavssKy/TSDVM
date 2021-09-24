#ifndef COMPLEX_HPP_INCLUDED
#define COMPLEX_HPP_INCLUDED

//====================================================================================

#include <iostream>
#include <cmath>

//====================================================================================

class complex
{
    private:
        double Re_;
        double Im_;

    public:
        complex ();
        complex (double Re, double Im);
        ~complex () {};

        double abs () const;
        void   print () const;

        complex operator+ () const;
};

//====================================================================================

const double INACCURACY = 1E-6;
const int ZERO = 0;

//====================================================================================

int is_equal (double fir_nmb, double sec_nmb);

//====================================================================================


#endif