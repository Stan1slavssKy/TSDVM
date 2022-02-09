#include "../hash_table/hash_table_impl.hpp"

#include <gtest/gtest.h> // NOLINT

using namespace s1ky; // NOLINT

const char* test_key_arr[] = { "Bob", "Steve", "John", "Erwin", "Eren" };

int test_value_arr[] = { 100, 100, 150, 10, 10000 };

TEST(CharIntHashTable, ValueConstructor)
{
    Hash_table<const char*, int> test(10);
    ASSERT_EQ(10, test.get_capacity());
}

TEST(CharIntHashTable, SetValue)
{
    Hash_table<const char*, int> test(4);

    for (int i = 0; i < 5; ++i)
    {
        test.set_value(test_key_arr[i], test_value_arr[i]);
        ASSERT_EQ(test_value_arr[i], test.get_value(test_key_arr[i]).value_or(-1));
    }
    test.set_value("Bob", 4);
}

TEST(CharIntHashTable, GetValue)
{
    Hash_table<const char*, int> test;

    for (int i = 0; i < 5; ++i)
    {
        test.set_value(test_key_arr[i], test_value_arr[i]);
        ASSERT_EQ(test_value_arr[i], test.get_value(test_key_arr[i]).value_or(-1));
    }

    ASSERT_EQ(-1, test.get_value("XXX").value_or(-1));
}

TEST(CharIntHashTable, Remove)
{
    Hash_table<const char*, int> test;

    for (int i = 0; i < 5; ++i)
    {
        test.set_value(test_key_arr[i], test_value_arr[i]);
        test.remove(test_key_arr[i]);
        ASSERT_EQ(-1, test.get_value(test_key_arr[i]).value_or(-1));
    }
}

TEST(CharIntHashTable, GetCapacity)
{
    Hash_table<const char*, int> test(23);
    ASSERT_EQ(23, test.get_capacity());
}

TEST(CharIntHashTable, GetSize)
{
    Hash_table<const char*, int> test;

    for (int i = 0; i < 5; ++i) { test.set_value(test_key_arr[i], test_value_arr[i]); }
    ASSERT_EQ(5, test.get_size());

    test.set_value("Bob", 4);
    ASSERT_EQ(5, test.get_size());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv); // NOLINT

    return RUN_ALL_TESTS(); // NOLINT
}