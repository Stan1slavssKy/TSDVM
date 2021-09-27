#ifndef TEST_H_INCLUDED 
#define TEST_H_INCLUDED

//====================================================================================

#define TEST(Re_z1, Im_z1, Re_z2, Im_z2, Res_Re, Res_Im, operator)\
{                                                                 \
    z1.Re = Re_z1;                                                \
    z1.Im = Im_z1;                                                \
    z2.Re = Re_z2;                                                \
    z2.Im = Im_z2;                                                \
                                                                  \
    z = z1 operator z2;                                           \
    if ((z.Re != Res_Re) || (z.Im != Res_Im))                     \
        std::cout << "bad test " << #operator << std::endl;       \
}                                                                 \

//====================================================================================

void unit_test ();

//====================================================================================

#endif