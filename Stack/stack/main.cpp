#include <iostream>
#include "stack.hpp"

//----------------------------------------------------------------------------------------------

int main ()
{
    s1ky::stack<bool> a;

    for (int i = 0; i < 100; i++)
    {
        a.push (1);
    }

    a.print ();

    return 0;
}

//----------------------------------------------------------------------------------------------