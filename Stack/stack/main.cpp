#include "stack_bool_impl.hpp"

#include <iostream>

int main()
{
    s1ky::stack<bool> a;

    for (int i = 0; i < 100; i++)
    {
        a.push(false);
        assert(false == a.top());
    }

    // a.print ();

    //std::cout << "stack top = " << stk.top() << std::endl;

    return 0;
}