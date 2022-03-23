#include "../typo_corrector/typo_corrector.hpp"

#include <gtest/gtest.h> // NOLINT

using namespace s1ky; // NOLINT

TEST(ClassTypoCorrector, IntegrationTest)
{
    Typo_corrector test;
    test.start_correcting("../../my.txt");
}

TEST(ClassDictionaryTest, LevDistanceCalculation)
{
    Dictionary  dict;
    std::string fir_w = "word";
    std::string sec_w = "w";

    ASSERT_EQ(3, dict.lev_distance_calculation(fir_w, sec_w));

    sec_w = sec_w + "o";
    ASSERT_EQ(2, dict.lev_distance_calculation(fir_w, sec_w));

    sec_w = sec_w + "r";
    ASSERT_EQ(1, dict.lev_distance_calculation(fir_w, sec_w));

    sec_w = sec_w + "d";
    ASSERT_EQ(0, dict.lev_distance_calculation(fir_w, sec_w));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv); // NOLINT

    return RUN_ALL_TESTS(); // NOLINT
}