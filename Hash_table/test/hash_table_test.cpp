#include "../hash_table/hash_table.hpp"

#include <gtest/gtest.h> // NOLINT

using namespace s1ky;

TEST(HashTable, InitTesting)
{

}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv); // NOLINT

    return RUN_ALL_TESTS(); // NOLINT
}