#include "../stack/stack_bool_impl.hpp"

#include <gtest/gtest.h>

namespace s1ky
{
    
// test for double stack

TEST(DoubleTest, TestPush)
{
    stack<double> test_stk;
    double        top_val = 0;

    for (int i = 0; i < 10000000; i++)
    {
        test_stk.push(i + i * 0.7);
        ASSERT_EQ(i + i * 0.7, test_stk.top());
    }
}

TEST(DoubleTest, TestPop)
{
    stack<double> test_stk;

    for (int i = 1; i < 10000000; i++)
    {
        test_stk.push(i - 0.2 * i);

        if (i % 3 == 0)
        {
            test_stk.pop();
            ASSERT_EQ(i - 1 - 0.2 * (i - 1), test_stk.top());
        }
    }
}

TEST(DoubleTest, TestISempty)
{
    stack<double> test_stk;

    ASSERT_EQ(1, test_stk.is_empty());

    test_stk.push(77.7);

    ASSERT_EQ(0, test_stk.is_empty());
}

TEST(DoubleTest, TestSize)
{
    stack<double> test_stk;

    for (int i = 0; i < 1000; i++) { test_stk.push(i); }

    ASSERT_EQ(test_stk.size(), 1000);

    for (int i = 0; i < 10000; i++) { test_stk.push(i); }

    ASSERT_EQ(test_stk.size(), 11000);
}

TEST(DoubleTest, TestTop)
{
    stack<double> test_stk;

    for (int i = 0; i < 100000; i++)
    {
        test_stk.push(i);
        ASSERT_EQ(i, test_stk.top());
    }
}

TEST(DoubleTest, TestConstTop)
{
    int number_of_iterations = 10;

    auto* data = new double[number_of_iterations] {};
    assert(data);

    for (int i = 0; i < number_of_iterations; i++) { data[i] = i; }

    const stack<double> test_stk(data, number_of_iterations);

    ASSERT_EQ(number_of_iterations - 1, test_stk.top());

    delete[] data;
}

TEST(DoubleTest, TestEQop)
{
    stack<double> fir_stk;
    stack<double> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(i); }

    sec_stk = fir_stk;

    ASSERT_EQ(fir_stk, sec_stk);
}

TEST(DoubleTest, TestISEQop)
{
    stack<double> fir_stk;
    stack<double> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(i); }

    bool res = (sec_stk == fir_stk);
    ASSERT_EQ(res, 0);

    sec_stk = fir_stk;
    res     = (sec_stk == fir_stk);
    ASSERT_EQ(res, 1);
}

TEST(DoubleTest, TestISNEQop)
{
    stack<double> fir_stk;
    stack<double> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(i); }

    bool res = (sec_stk != fir_stk);
    ASSERT_EQ(res, 1);

    sec_stk = fir_stk;
    res     = (sec_stk != fir_stk);
    ASSERT_EQ(res, 0);
}

stack<double> get_double_stack()
{
    stack<double> stk;

    for (int i = 0; i < 100; i++) { stk.push(i); }

    return stk;
}

TEST(DoubleTest, TestMoveEQop)
{
    stack<double> fir_stack;

    for (int i = 0; i < 100; i++) { fir_stack.push(i); }

    stack<double> sec_stk = get_double_stack();

    ASSERT_EQ(fir_stack, sec_stk);
}

//==================================================================
// tests for bool stack

TEST(BoolTest, TestPush)
{
    stack<bool> test_stk;

    for (int i = 0; i < 1000000; i++)
    {
        test_stk.push(true);
        test_stk.push(false);
        ASSERT_EQ(false, test_stk.top());
    }
}

TEST(BoolTest, TestPop)
{
    stack<bool> test_stk;

    for (int i = 1; i < 1000000; i++)
    {
        test_stk.push(true);

        if (i % 3 == 0)
        {
            test_stk.pop();
            ASSERT_EQ(true, test_stk.top());
        }
    }
}

TEST(BoolTest, TestISempty)
{
    stack<bool> test_stk;

    ASSERT_EQ(1, test_stk.is_empty());

    test_stk.push(true);

    ASSERT_EQ(0, test_stk.is_empty());
}

TEST(BoolTest, TestSize)
{
    stack<bool> test_stk;

    for (int i = 0; i < 1000; i++) { test_stk.push(true); }

    ASSERT_EQ(test_stk.size(), 1000);

    for (int i = 0; i < 10000; i++) { test_stk.push(false); }

    ASSERT_EQ(test_stk.size(), 11000);
}

TEST(BoolTest, TestTop)
{
    stack<bool> test_stk;

    for (int i = 0; i < 100000; i++)
    {
        test_stk.push(true);
        ASSERT_EQ(true, test_stk.top());
    }

    for (int i = 0; i < 100000; i++)
    {
        test_stk.push(false);
        ASSERT_EQ(false, test_stk.top());
    }
}

TEST(BoolTest, TestEQop)
{
    stack<bool> fir_stk;
    stack<bool> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(true); }

    sec_stk = fir_stk;

    ASSERT_EQ(fir_stk, sec_stk);
}

TEST(BoolTest, TestISEQop)
{
    stack<bool> fir_stk;
    stack<bool> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(false); }

    bool res = (sec_stk == fir_stk);
    ASSERT_EQ(res, 0);

    sec_stk = fir_stk;
    res     = (sec_stk == fir_stk);
    ASSERT_EQ(res, 1);
}

TEST(BoolTest, TestISNEQop)
{
    stack<bool> fir_stk;
    stack<bool> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(true); }

    bool res = (sec_stk != fir_stk);
    ASSERT_EQ(res, 1);

    sec_stk = fir_stk;
    res     = (sec_stk != fir_stk);
    ASSERT_EQ(res, 0);
}

stack<bool> get_bool_stack()
{
    stack<bool> stk;

    for (int i = 0; i < 100; i++) { stk.push(true); }

    return stk;
}

TEST(BoolTest, TestMoveEQop)
{
    stack<bool> fir_stack;

    for (int i = 0; i < 100; i++) { fir_stack.push(true); }

    stack<bool> sec_stk = get_bool_stack();

    ASSERT_EQ(fir_stack, sec_stk);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

} //namespace s1ky