#include <iostream>
#include "stack_bool_impl.hpp"

int main ()
{
    s1ky::stack<bool> a;

    for (int i = 0; i < 10; i++)
    {
        a.push (true);
        a.push (true);
        a.push (true);
        a.push (false);
    }
    
    a.print ();

    return 0;
}