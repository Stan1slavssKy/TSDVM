#ifndef COMPLEX_HPP_INCLUDED
#define COMPLEX_HPP_INCLUDED

//====================================================================================

struct complex
{
    double Re;
    double Im;

    complex ();
    complex (double Re, double Im);
    ~complex () {};
    
    void print () const;
    double abs () const;
    double arg () const;

    complex& operator= (const complex& nmb);

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

void unit_test ();

void testing_arifm (const complex& z1, const complex& z2, double res_Re, double res_Im,
                            complex (*operator_func)(const complex&), int* test_number);
//====================================================================================

#endif