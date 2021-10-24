#include <iostream>
#include "stack_bool_impl.hpp"

int main ()
{
    s1ky::stack<bool> a;
 s1ky::stack<bool> b;

    a.push (true);
    a.push (false);
    a.push (true);
    a.push (true);
    a.push (false);
    a.push (true);
    a.push (true);
    a.push (true);
    a.push (false);
    a.push (true);
    a.pop ();

    if (a == b)
    {
        std::cout << "yes" << std::endl;
    }
    if (a != b)
    {
        std::cout << "no" << std::endl;
    }

    std::cout << "stack top = " << a.top () << std::endl;

    a.print ();

    return 0;
}