#include "compl.hpp"
#include <iostream>
#include <cmath>

//====================================================================================

const double INACCURACY = 1E-6;

//====================================================================================

bool is_equal (double fir_nmb, double sec_nmb);

//====================================================================================

bool is_equal (double fir_nmb, double sec_nmb)
{
    return (fabs (fir_nmb - sec_nmb) <= INACCURACY);
}

complex::complex () :
    Re(0),
    Im(0)
    {}

complex::complex (double Re, double Im) :
    Re(Re),
    Im(Im)
    {}

double complex::abs () const
{
    return Re * Re + Im * Im;
}

double complex::arg () const
{
    return atan (Im/Re);
}

void complex::print () const
{
    if (is_equal (Im, 0) && is_equal (Re, 0))
        std::cout << "0" << std::endl;

    else if (is_equal (Im, 0))
        std::cout << Re << std::endl;    

    else if (is_equal (Re, 0))
        std::cout << "i * " << Im << std::endl;    

    else 
        std::cout << Re << " + i * " << Im << std::endl;
}

complex& complex::operator= (const complex& nmb)
{
    this -> Im = nmb.Re;
    this -> Re = nmb.Im;

    return *this;
}

complex complex::operator+ (const complex& nmb) const
{   
    complex sum;

    sum.Re = Re + nmb.Re;
    sum.Im = Im + nmb.Im;

    return sum;
}

complex complex::operator- (const complex& nmb) const
{   
    complex sub;

    sub.Re = Re - nmb.Re;
    sub.Im = Im - nmb.Im;

    return sub;
}

complex complex::operator* (const complex& nmb) const
{   
    complex mul;

    mul.Re = Re * nmb.Re - Im * nmb.Im;
    mul.Im = Re * nmb.Im + nmb.Re * Im;

    return mul;
}

complex complex::operator/ (const complex& nmb) const
{   
    complex div;

    div.Re = (Re * nmb.Re + Im * nmb.Im) / (nmb.Im * nmb.Im + nmb.Re * nmb.Re);
    div.Im = (nmb.Re * Im - Re * nmb.Im) / (nmb.Im * nmb.Im + nmb.Re * nmb.Re);

    return div;
}

bool complex::operator== (const complex& nmb) const
{
    return (Re == nmb.Re && Im == nmb.Im);
}

bool complex::operator!= (const complex& nmb) const
{
    return !(Re == nmb.Re && Im == nmb.Im); 
}

complex& complex::operator+= (const complex& nmb)
{
    double temp_Re = Re;
    double temp_Im = Im;

    Re = temp_Re + nmb.Re;
    Im = temp_Im + nmb.Im;

    return *this;
}

complex& complex::operator-= (const complex& nmb)
{
    double temp_Re = Re;
    double temp_Im = Im;

    Re = temp_Re - nmb.Re;
    Im = temp_Im - nmb.Im;

    return *this;
}

complex& complex::operator*= (const complex& nmb)
{
    double temp_Re = Re;
    double temp_Im = Im;

    Re = temp_Re * nmb.Re - temp_Im * nmb.Im;
    Im = temp_Re * nmb.Im + nmb.Re * temp_Im;

    return *this;
}

complex& complex::operator/= (const complex& nmb)
{
    double temp_Re = Re;
    double temp_Im = Im;

    Re = (temp_Re * nmb.Re + temp_Im * nmb.Im) / (nmb.Im * nmb.Im + nmb.Re * nmb.Re);
    Im = (nmb.Re * temp_Im - temp_Re * nmb.Im) / (nmb.Im * nmb.Im + nmb.Re * nmb.Re);

    return *this;
}

//====================================================================================