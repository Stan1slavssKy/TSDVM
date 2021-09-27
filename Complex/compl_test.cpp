#include "compl.hpp"

//====================================================================================
/*
enum operator_func
{
    ADD = 1,
    SUB = 2,
    MUL = 3,
};
*/

//====================================================================================

void unit_test ()
{
    complex z1;
    complex z2;

    int test_number = 0;

    //testing_arifm (z1, z2, 4, 3, complex::operator+, &test_number);
}

//====================================================================================

void testing_arifm (const complex& z1, const complex& z2, double res_Re, double res_Im,
                            complex(* operator_func)(const complex&), int* test_number)
{
    /*test_number++;

    complex res = z1.operator_func(z2);

    if (res.Re == res_Re && res.Im_ == res_Im)
        std::cout << "success, test number = " << test_number << std::endl;
    else 
        std::cout << "not success, test number = " << test_number << std::endl;*/
}

//====================================================================================