#include "compl.hpp"

//====================================================================================

complex::complex (double Re, double Im) :
    Re_(Re),
    Im_(Im)
    {}

//====================================================================================

double complex::abs () const
{
    return Re_ * Re_ - Im_ * Im_;
}

//====================================================================================

void complex::print () const
{
    if (is_equal (Im_, ZERO) && is_equal (Re_, ZERO))
        std::cout << "0" << std::endl;

    else if (is_equal (Im_, ZERO))
        std::cout << Re_ << std::endl;    

    else if (is_equal (Re_, ZERO))
        std::cout << "i * " << Im_ << std::endl;    

    else 
        std::cout << Re_ << " + i * " << Im_ << std::endl;
}

//====================================================================================

complex complex::operator+ () const
{   
    
}

//====================================================================================

int is_equal (double fir_nmb, double sec_nmb)
{
    return (fabs (fir_nmb - sec_nmb) <= INACCURACY);
}

//====================================================================================