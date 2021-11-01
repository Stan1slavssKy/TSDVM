#include "stack_bool_impl.hpp"

#include <iostream>

int main()
{
    s1ky::stack<bool> a;
    s1ky::stack<bool> b;

    for (int i = 0; i < 1000000; i++)
    {
        a.push(false);
        assert(false == a.top());
    }

    // a.print ();

    std::cout << "stack top = " << a.top() << std::endl;

    return 0;
}