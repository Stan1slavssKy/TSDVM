#include "compl.hpp"

//=======================================================

complex::complex (double Re, double Im)
{
    Re_ = Re;
    Im_ = Im;
}

//=======================================================

double complex::abs ()
{
    return Re_ * Re_ + Im_ * Im_;
}

//=======================================================

void complex::print ()
{
    std::cout << "complex number z = " << Re_ << " + i * " << Im_ << std::endl;
}

//=======================================================