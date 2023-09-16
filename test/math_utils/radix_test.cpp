#include "math_utils/radix.hpp"

#include <gtest/gtest.h>

#include <string>

TEST(RadixTest, ZeroBase10To2) {
    std::string result = base_10_to_n(0, 2);
    EXPECT_EQ(result, "0");
}

TEST(RadixTest, ZeroBase2To10) {
    long long result = base_n_to_10("0", 2);
    EXPECT_EQ(result, 0);
}

TEST(RadixTest, Base10To2) {
    std::string result = base_10_to_n(13, 2);
    EXPECT_EQ(result, "1101");
}

TEST(RadixTest, Base2To10) {
    long long result = base_n_to_10("1101", 2);
    EXPECT_EQ(result, 13);
}

TEST(RadixTest, Large) {
    long long expected = 1'000'000'000'000'000'000LL;
    std::string base9 = base_10_to_n(expected, 9);
    long long result = base_n_to_10(base9, 9);
    EXPECT_EQ(result, expected);
}