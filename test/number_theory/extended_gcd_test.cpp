#include <gtest/gtest.h>

#include "number_theory/extended_gcd.hpp"

TEST(ExtendedGcdTest, GreaterThan) {
    auto [d, x, y] = extended_gcd(7, 3);
    EXPECT_EQ(d, 1);
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, -2);
}

TEST(ExtendedGcdTest, LessThan) {
    auto [d, x, y] = extended_gcd(3, 7);
    EXPECT_EQ(d, 1);
    EXPECT_EQ(x, 5);
    EXPECT_EQ(y, -2);
}

TEST(ExtendedGcdTest, Equal) {
    auto [d, x, y] = extended_gcd(3, 3);
    EXPECT_EQ(d, 3);
    EXPECT_EQ(x, 0);
    EXPECT_EQ(y, 1);
}

TEST(ExtendedGcdTest, Large) {
    auto [d, x, y] = extended_gcd(1'000'000'000'000'000'000, 999'999'999'999'999'999);
    EXPECT_EQ(d, 1);
    EXPECT_EQ(x, 1);
    EXPECT_EQ(y, -1);
}

TEST(ExtendedGcdTest, Zero) {
    EXPECT_DEATH(extended_gcd(0, 1), "");
}
