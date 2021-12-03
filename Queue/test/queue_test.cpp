#include "../list_impl/queue_impl.hpp"
#include "../stack_impl/queue/queue_impl.hpp"

#include <gtest/gtest.h> // NOLINT

#ifdef STACK_IMPL
using namespace s1ky::stack_queue;
#endif

#ifdef LIST_IMPL
using namespace s1ky::list_queue;
#endif

TEST(DoubleQueueTest, ParameterConstructTest) // NOLINT
{
    for (size_t i = 0; i < 100000; i++)
    {
        Queue<double> qu(0.7 * static_cast<double>(i));
        ASSERT_EQ(0.7 * static_cast<double>(i), qu.front()); // NOLINT
    }
}

TEST(DoubleQueueTest, CopyConstructTest) // NOLINT
{
    for (size_t i = 0; i < 100000; i++)
    {
        Queue<double> qu(0.7 * static_cast<double>(i));
        Queue<double> qu2 = qu;
        ASSERT_EQ(qu2.front(), qu.front()); // NOLINT
    }
}

Queue<double> get_queue_for_constr()
{
    Queue<double> qu(27.3);
    return qu;
}

TEST(DoubleQueueTest, MoveConstructor) // NOLINT
{
    Queue<double> qu1(get_queue_for_constr());

    ASSERT_EQ(27.3, qu1.front()); // NOLINT
}

TEST(DoubleQueueTest, Push) // NOLINT
{
    Queue<double> qu;

    for (size_t i = 0; i < 1000000; i++)
    {
        double value = 0.7 * static_cast<double>(i);
        qu.push(value);
        ASSERT_EQ(qu.back(), value); // NOLINT
    }
}

TEST(DoubleQueueTest, Pop) // NOLINT
{
    Queue<double> qu;
    double        value = 0;

    qu.push(30);

    for (int i = 0; i < 1000000; i++)
    {
        value = 0.8 * i;
        qu.push(value);
        qu.pop();
        ASSERT_EQ(value, qu.front()); // NOLINT
    }
}

TEST(DoubleQueueTest, Emty) // NOLINT
{
    Queue<double> qu;
    ASSERT_EQ(true, qu.empty()); // NOLINT

    qu.push(47.65);
    ASSERT_EQ(false, qu.empty()); // NOLINT

    qu.pop();
    ASSERT_EQ(true, qu.empty()); // NOLINT
}

TEST(DoubleQueueTest, Size) // NOLINT
{
    Queue<double> qu;
    ASSERT_EQ(0, qu.size()); // NOLINT

    for (int i = 0; i < 10000; i++) { qu.push(i); }

    ASSERT_EQ(10000, qu.size()); // NOLINT
}

TEST(DoubleQueueTest, Front) // NOLINT
{
    Queue<double> qu;
    double        value = 0;

    qu.push(value);

    for (int i = 1; i < 1000000; i++)
    {
        value = 0.3 * i;
        qu.push(value);
        qu.pop();

        ASSERT_EQ(qu.front(), value); // NOLINT
    }
}

TEST(DoubleQueueTest, Back) // NOLINT
{
    Queue<double> qu;

    double value = 0;

    for (int i = 1; i < 1000000; i++)
    {
        value = 0.3 * i;
        qu.push(value);

        ASSERT_EQ(qu.back(), value); // NOLINT

        if (i % 5 == 0)
        {
            qu.pop();
        }
    }
}

TEST(DoubleQueueTest, OperatorEqual) // NOLINT
{
    Queue<double> qu1;
    Queue<double> qu2;

    for (int i = 0; i < 10000; i++)
    {
        qu1.push(i);
        qu2.push(i);
        ASSERT_EQ(qu1, qu2); // NOLINT
    }
}

TEST(DoubleQueueTest, OpeartorNotEqual) // NOLINT
{
    Queue<double> qu1;
    Queue<double> qu2;

    for (int i = 0; i < 10000; i++)
    {
        qu1.push(i);
        ASSERT_NE(qu1, qu2); // NOLINT
    }
}

TEST(DoubleQueueTest, СopyOperatorAssigment) // NOLINT
{
    Queue<double> qu1;
    Queue<double> qu2;
    for (int i = 0; i < 100000; i++) { qu1.push(i); }

    ASSERT_EQ(qu1, qu1); // NOLINT

    qu2 = qu1;
    ASSERT_EQ(qu1, qu2); // NOLINT

    ASSERT_EQ(qu2, qu2); // NOLINT
}

Queue<double> get_move_operator_queue()
{
    Queue<double> qu;
    for (int i = 0; i < 100000; i++) { qu.push(i); }

    return qu;
}

TEST(DoubleQueueTest, MoveOperatorAssigment) // NOLINT
{
    Queue<double> qu1;
    Queue<double> qu2;

    qu1 = get_move_operator_queue();

    for (int i = 0; i < 100000; i++) { qu2.push(i); }

    ASSERT_EQ(qu1, qu2); // NOLINT
}

TEST(DoubleQueueTest, Swap) // NOLINT
{
    Queue<double> qu1;
    Queue<double> qu2;
    Queue<double> temp;

    for (int i = 0; i < 100; i++) { qu1.push(i); }

    for (int i = 100; i < 200; i++)
    {
        qu2.push(i);
        temp.push(i);
    }

    qu1.swap(&qu2);
    ASSERT_EQ(qu1, temp); // NOLINT
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv); // NOLINT

    return RUN_ALL_TESTS(); // NOLINT
}