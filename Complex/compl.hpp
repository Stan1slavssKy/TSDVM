#ifndef COMPLEX_HPP_INCLUDED
#define COMPLEX_HPP_INCLUDED

//====================================================================================

#include <iostream>
#include <cmath>

//====================================================================================

class complex
{
    public:
        double Re_;
        double Im_;

        complex ();
        complex (double Re, double Im);
        ~complex () {};
        
        void print () const;
        double abs () const;
        double arg () const;

        complex operator+ (const complex& nmb) const;
        complex operator- (const complex& nmb) const;
        complex operator* (const complex& nmb) const;
        complex operator/ (const complex& nmb) const;

        bool operator== (const complex& nmb) const;
        bool operator!= (const complex& nmb) const;

        complex& operator+= (const complex& nmb);
        complex& operator-= (const complex& nmb);
        complex& operator*= (const complex& nmb);
        complex& operator/= (const complex& nmb);
};

//====================================================================================

const double INACCURACY = 1E-6;
const int ZERO = 0;

//====================================================================================

bool is_equal (double fir_nmb, double sec_nmb);

void unit_test ();

void testing_complex (const complex& z1, const complex& z2, double res_Re, double res_Im, complex (*operator_func)(const complex&));

//====================================================================================

#endif