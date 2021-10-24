#include <iostream>
#include "stack_bool_impl.hpp"

int main ()
{
    s1ky::stack<bool> a;

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
    
    std::cout << "stack top = " << a.top () << std::endl;

    a.print ();

    return 0;
}