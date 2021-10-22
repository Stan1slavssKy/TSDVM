#include <iostream>
#include "stack_bool_impl.hpp"

int main ()
{
    s1ky::stack<bool> a;

    for (int i = 0; i < 1600000; i++)
    {
        a.push (true);
    }

    a.print ();

    for (int i = 0; i < 1600000; i++)
    {
            a.pop ();
    }

    a.print ();

    return 0;
}