#include "queue_impl.hpp"

namespace s1ky
{
queue<double> get_queue()
{
    queue<double> a;
    return a;
}

int main ()
{
    queue<double>(get_queue());
    return 0;
}
}