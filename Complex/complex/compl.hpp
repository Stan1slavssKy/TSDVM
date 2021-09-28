#ifndef COMPLEX_HPP_INCLUDED
#define COMPLEX_HPP_INCLUDED

//====================================================================================

struct complex
{
    double Re;
    double Im;

    complex ();
    complex (double Re, double Im);
    complex (const complex& nmb);

    ~complex () {};
    
    void print () const;
    double abs () const;
    double arg () const;

    complex& operator= (const complex& nmb);

    complex  operator- ();
    complex& operator+ ();

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

    complex operator- (double nmb) const;
    complex operator+ (double nmb) const;
    complex operator* (double nmb) const;
    complex operator/ (double nmb) const;
};

//====================================================================================

#endif