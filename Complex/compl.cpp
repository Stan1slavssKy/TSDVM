#include "compl.hpp"

//====================================================================================

complex::complex () :
    Re_(0),
    Im_(0)
    {}

//====================================================================================

complex::complex (double Re, double Im) :
    Re_(Re),
    Im_(Im)
    {}

//====================================================================================

bool is_equal (double fir_nmb, double sec_nmb)
{
    return (fabs (fir_nmb - sec_nmb) <= INACCURACY);
}

//====================================================================================

double complex::abs () const
{
    return Re_ * Re_ + Im_ * Im_;
}

//====================================================================================

double complex::arg () const
{
    return atan (Im_/Re_);
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

complex complex::operator+ (const complex& nmb) const
{   
    complex sum;

    sum.Re_ = Re_ + nmb.Re_;
    sum.Im_ = Im_ + nmb.Im_;

    return sum;
}

//====================================================================================

complex complex::operator- (const complex& nmb) const
{   
    complex sub;

    sub.Re_ = Re_ - nmb.Re_;
    sub.Im_ = Im_ - nmb.Im_;

    return sub;
}

//====================================================================================

complex complex::operator* (const complex& nmb) const
{   
    complex mul;

    mul.Re_ = Re_ * nmb.Re_ - Im_ * nmb.Im_;
    mul.Im_ = Re_ * nmb.Im_ + nmb.Re_ * Im_;

    return mul;
}

//====================================================================================

complex complex::operator/ (const complex& nmb) const
{   
    complex div;

    div.Re_ = (Re_ * nmb.Re_ + Im_ * nmb.Im_) / (nmb.Im_ * nmb.Im_ + nmb.Re_ * nmb.Re_);
    div.Im_ = (nmb.Re_ * Im_ - Re_ * nmb.Im_) / (nmb.Im_ * nmb.Im_ + nmb.Re_ * nmb.Re_);

    return div;
}

//====================================================================================

bool complex::operator== (const complex& nmb) const
{
    return (Re_ == nmb.Re_ && Im_ == nmb.Im_);
}

//====================================================================================

bool complex::operator!= (const complex& nmb) const
{
    return !(Re_ == nmb.Re_ && Im_ == nmb.Im_); 
}

//====================================================================================

complex& complex::operator+= (const complex& nmb)
{
    double temp_Re = Re_;
    double temp_Im = Im_;

    Re_ = temp_Re + nmb.Re_;
    Im_ = temp_Im + nmb.Im_;

    return *this;
}

//====================================================================================

complex& complex::operator-= (const complex& nmb)
{
    double temp_Re = Re_;
    double temp_Im = Im_;

    Re_ = temp_Re - nmb.Re_;
    Im_ = temp_Im - nmb.Im_;

    return *this;
}

//====================================================================================

complex& complex::operator*= (const complex& nmb)
{
    double temp_Re = Re_;
    double temp_Im = Im_;

    Re_ = temp_Re * nmb.Re_ - temp_Im * nmb.Im_;
    Im_ = temp_Re * nmb.Im_ + nmb.Re_ * temp_Im;

    return *this;
}

//====================================================================================

complex& complex::operator/= (const complex& nmb)
{
    double temp_Re = Re_;
    double temp_Im = Im_;

    Re_ = (temp_Re * nmb.Re_ + temp_Im * nmb.Im_) / (nmb.Im_ * nmb.Im_ + nmb.Re_ * nmb.Re_);
    Im_ = (nmb.Re_ * temp_Im - temp_Re * nmb.Im_) / (nmb.Im_ * nmb.Im_ + nmb.Re_ * nmb.Re_);

    return *this;
}

//====================================================================================