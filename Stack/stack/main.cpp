#include "stack_bool_impl.hpp"

#include <iostream>

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
    a.push (false);

    std::cout << "stack top = " << a.top () << std::endl;

    a.print ();

    return 0;
}