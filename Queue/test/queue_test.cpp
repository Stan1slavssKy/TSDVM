#include "../list_impl/queue_impl.hpp"

#include <gtest/gtest.h>  // NOLINT

namespace s1ky {

TEST(QueueTest, ParameterConstructTest)
{
    double data[] = {1.1, 2, 3, 4, 7, 9, 10};
    Queue<double> test_queue(data);
}

TEST(QueueTest, CopyConstructTest)
{

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

} // namespace s1ky