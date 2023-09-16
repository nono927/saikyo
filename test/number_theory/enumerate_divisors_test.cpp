#include "number_theory/enumerate_divisors.hpp"

#include <gtest/gtest.h>

#include <vector>

TEST(EnumerateDivisorsTest, One) {
    std::vector<long long> actual = enumerate_divisors(1);
    std::vector<long long> expected = {1};
    EXPECT_EQ(actual, expected);
}

TEST(EnumerateDivisorsTest, Prime) {
    std::vector<long long> actual = enumerate_divisors(13);
    std::vector<long long> expected = {1, 13};
    EXPECT_EQ(actual, expected);
}

TEST(EnumerateDivisorsTest, Square) {
    std::vector<long long> actual = enumerate_divisors(16);
    std::vector<long long> expected = {1, 2, 4, 8, 16};
    EXPECT_EQ(actual, expected);
}

TEST(EnumerateDivisorsTest, HighlyCompositeNumber) {
    std::vector<long long> actual = enumerate_divisors(24);
    std::vector<long long> expected = {1, 2, 3, 4, 6, 8, 12, 24};
    EXPECT_EQ(actual, expected);
}