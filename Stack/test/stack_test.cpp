#include "../stack/stack_impl.hpp"

#include <gtest/gtest.h>

namespace s1ky {

// test for double Stack

TEST(DoubleTest, TestPush)
{
    Stack<double> test_stk;

    for (int i = 0; i < 10000000; i++)
    {
        test_stk.push(i + i * 0.7);
        ASSERT_EQ(i + i * 0.7, test_stk.top());
    }
}

TEST(DoubleTest, TestPop)
{
    Stack<double> test_stk;

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
    Stack<double> test_stk;

    ASSERT_EQ(1, test_stk.is_empty());

    test_stk.push(77.7);

    ASSERT_EQ(0, test_stk.is_empty());
}

TEST(DoubleTest, TestSize)
{
    Stack<double> test_stk;

    for (int i = 0; i < 1000; i++) { test_stk.push(i); }

    ASSERT_EQ(test_stk.size(), 1000);

    for (int i = 0; i < 10000; i++) { test_stk.push(i); }

    ASSERT_EQ(test_stk.size(), 11000);
}

TEST(DoubleTest, TestTop)
{
    Stack<double> test_stk;

    for (int i = 0; i < 100000; i++)
    {
        test_stk.push(i);
        ASSERT_EQ(i, test_stk.top());
    }
}

TEST(DoubleTest, TestConstTop)
{
    size_t number_of_iterations = 10;

    auto* data = new double[number_of_iterations] {};
    assert(data);

    for (size_t i = 0; i < number_of_iterations; i++) { data[i] = static_cast<double>(i); }

    const Stack<double> test_stk(data, number_of_iterations);

    ASSERT_EQ(number_of_iterations - 1, test_stk.top());

    delete[] data;
}

TEST(DoubleTest, TestEQop)
{
    Stack<double> fir_stk;
    Stack<double> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(i); }

    sec_stk = fir_stk;

    ASSERT_EQ(fir_stk, sec_stk);
}

TEST(DoubleTest, TestISEQop)
{
    Stack<double> fir_stk;
    Stack<double> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(i); }

    bool res = (sec_stk == fir_stk);
    ASSERT_EQ(res, 0);

    sec_stk = fir_stk;
    res     = (sec_stk == fir_stk);
    ASSERT_EQ(res, 1);
}

TEST(DoubleTest, TestISNEQop)
{
    Stack<double> fir_stk;
    Stack<double> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(i); }

    bool res = (sec_stk != fir_stk);
    ASSERT_EQ(res, 1);

    sec_stk = fir_stk;
    res     = (sec_stk != fir_stk);
    ASSERT_EQ(res, 0);
}

Stack<double> get_double_Stack()
{
    Stack<double> stk;

    for (int i = 0; i < 100; i++) { stk.push(i); }

    return stk;
}

TEST(DoubleTest, TestMoveEQop)
{
    Stack<double> fir_stack;

    for (int i = 0; i < 100; i++) { fir_stack.push(i); }

    Stack<double> sec_stk = get_double_Stack();

    ASSERT_EQ(fir_stack, sec_stk);
}

//==================================================================
// tests for bool Stack

TEST(BoolTest, TestPush)
{
    Stack<bool> test_stk;

    for (int i = 0; i < 1000000; i++)
    {
        test_stk.push(true);
        test_stk.push(false);
        ASSERT_EQ(false, test_stk.top());
    }
}

TEST(BoolTest, TestPop)
{
    Stack<bool> test_stk;

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
    Stack<bool> test_stk;

    ASSERT_EQ(1, test_stk.is_empty());

    test_stk.push(true);

    ASSERT_EQ(0, test_stk.is_empty());
}

TEST(BoolTest, TestSize)
{
    Stack<bool> test_stk;

    for (int i = 0; i < 1000; i++) { test_stk.push(true); }

    ASSERT_EQ(test_stk.size(), 1000);

    for (int i = 0; i < 10000; i++) { test_stk.push(false); }

    ASSERT_EQ(test_stk.size(), 11000);
}

TEST(BoolTest, TestTop)
{
    Stack<bool> test_stk;

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
    Stack<bool> fir_stk;
    Stack<bool> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(true); }

    sec_stk = fir_stk;

    ASSERT_EQ(fir_stk, sec_stk);
}

TEST(BoolTest, TestISEQop)
{
    Stack<bool> fir_stk;
    Stack<bool> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(false); }

    bool res = (sec_stk == fir_stk);
    ASSERT_EQ(res, 0);

    sec_stk = fir_stk;
    res     = (sec_stk == fir_stk);
    ASSERT_EQ(res, 1);
}

TEST(BoolTest, TestISNEQop)
{
    Stack<bool> fir_stk;
    Stack<bool> sec_stk;

    for (int i = 0; i < 10000; i++) { fir_stk.push(true); }

    bool res = (sec_stk != fir_stk);
    ASSERT_EQ(res, 1);

    sec_stk = fir_stk;
    res     = (sec_stk != fir_stk);
    ASSERT_EQ(res, 0);
}

Stack<bool> get_bool_Stack()
{
    Stack<bool> stk;

    for (int i = 0; i < 100; i++) { stk.push(true); }

    return stk;
}

TEST(BoolTest, TestMoveEQop)
{
    Stack<bool> fir_stack;

    for (int i = 0; i < 100; i++) { fir_stack.push(true); }

    Stack<bool> sec_stk = get_bool_Stack();

    ASSERT_EQ(fir_stack, sec_stk);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

} // namespace s1ky