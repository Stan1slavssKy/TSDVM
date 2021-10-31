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

TEST (stack_test, test_is_empty)
{
    stack<double> test_stk;

    ASSERT_EQ (1, test_stk.is_empty ());

    test_stk.push (77.7);

    ASSERT_EQ (0, test_stk.is_empty ());
}

TEST (stack_test, test_size)
{
    stack<double> test_stk;

    for (int i = 0; i < 1000; i++)
    {
        test_stk.push (i);
    }

    ASSERT_EQ (test_stk.size (), 1000);

    for (int i = 0; i < 10000; i++)
    {
        test_stk.push (i);
    }

    ASSERT_EQ (test_stk.size (), 11000);
}

TEST (stack_test, test_top)
{
    stack<double> test_stk;

    for (int i = 0; i < 100000; i++)
    {
        test_stk.push (i);
        ASSERT_EQ (i, test_stk.top ());
    }
}

TEST (stack_test, test_const_top)
{
    int number_of_iterations = 10;

    double* data = new double[number_of_iterations] {};
    assert (data);

    for (int i = 0; i < number_of_iterations; i++)
    {
        data[i] = i;
    }

    const stack<double> test_stk(data, number_of_iterations);

    ASSERT_EQ (number_of_iterations - 1, test_stk.top ());

    delete[] data;
}

TEST (stack_test, test_eq_op)
{
    stack<double> fir_stk;
    stack<double> sec_stk;

    for (int i = 0; i < 10000; i++)
    {
        fir_stk.push (i);
    }

    sec_stk = fir_stk;

    ASSERT_EQ (fir_stk, sec_stk);
}

TEST (stack_test, test_iseq_op)
{
    stack<double> fir_stk;
    stack<double> sec_stk;

    for (int i = 0; i < 10000; i++)
    {
        fir_stk.push (i);
    }

    bool res = (sec_stk == fir_stk);
    ASSERT_EQ (res, 0);

    sec_stk = fir_stk;
    res = (sec_stk == fir_stk);
    ASSERT_EQ (res, 1);
}

TEST (stack_test, test_isneq_op)
{
    stack<double> fir_stk;
    stack<double> sec_stk;

    for (int i = 0; i < 10000; i++)
    {
        fir_stk.push (i);
    }

    bool res = (sec_stk != fir_stk);
    ASSERT_EQ (res, 1);

    sec_stk = fir_stk;
    res = (sec_stk != fir_stk);
    ASSERT_EQ (res, 0);
}

stack<double> get_stack ()
{
    stack<double> stk;

    for (int i = 0; i < 100; i++)
    {
        stk.push (i);
    }

    return stk;
}

TEST (stack_test, test_move_eq_op)
{
    stack<double> fir_stack;
    
    for (int i = 0; i < 100; i++)
    {
        fir_stack.push (i);
    }

    stack<double> sec_stk = get_stack ();

    ASSERT_EQ (fir_stack, sec_stk);
}

int main (int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}