#include <iostream>
#include "stack_bool_impl.hpp"

int main ()
{
    s1ky::stack<bool> a;

    a.push (false);
    a.push (true);
    a.push (false);
    a.push (true);
    a.push (true);
    a.push (true);
    a.push (false);
    a.push (false);

//pushing 01011100 in 1 byte === 92

    a.print ();

    return 0;
}