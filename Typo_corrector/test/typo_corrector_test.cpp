#include "../typo_corrector/typo_corrector.hpp"

#include <gtest/gtest.h> // NOLINT

using namespace s1ky; // NOLINT

TEST(Test, Test)
{
    Typo_corrector test;
    test.test();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv); // NOLINT

    return RUN_ALL_TESTS(); // NOLINT
}