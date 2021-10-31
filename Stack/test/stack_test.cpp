#include "../stack/stack_bool_impl.hpp"

#include <gtest/gtest.h>

using namespace s1ky;

TEST (stack_test, test_push)
{
    stack<double> test_stk;
    double top_val = 0;

    for (int i = 0; i < 10000000; i++)
    {
        test_stk.push (i + i * 0.7);
        ASSERT_EQ (i + i * 0.7, test_stk.top ());
    }
}

TEST (stack_test, test_pop)
{
    stack<double> test_stk;

    for (int i = 1; i < 10000000; i++)
    {
        test_stk.push (i - 0.2 * i);

        if (i % 3 == 0)
        {
            test_stk.pop ();
            ASSERT_EQ (i - 1 - 0.2 * (i - 1), test_stk.top ());
        }
    }
}

int main (int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}