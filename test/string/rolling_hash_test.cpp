#include "string/rolling_hash.hpp"

#include <gtest/gtest.h>

TEST(RollingHashTest, ConstructFromString) {
    RollingHash("helloworld");
    std::string contain_zero = "helloworld";
    contain_zero[4] = '\0';
    EXPECT_DEATH((RollingHash(contain_zero)), "");
}

TEST(RollingHashTest, ConstructFromVector) {
    RollingHash({1, -2, 3, -4, 5});
    EXPECT_DEATH(RollingHash({0, 0, 0}), "");
}

TEST(RollingHashTest, OneVec) {
    RollingHash h({1, -1, 1, -1});
    EXPECT_EQ(h(0, 1), h(2, 3));
    EXPECT_EQ(h(1, 2), h(3, 4));
    EXPECT_EQ(h(0, 2), h(2, 4));
    EXPECT_NE(h(0, 1), h(1, 2));
    EXPECT_NE(h(0, 2), h(1, 3));
}

TEST(RollingHashTest, TwoVec) {
    RollingHash h1("aab");
    RollingHash h2("abb");
    EXPECT_EQ(h1(1, 3), h2(0, 2));
    EXPECT_EQ(h1(0, 1), h2(0, 1));
    EXPECT_EQ(h1(2, 3), h2(2, 3));
    EXPECT_NE(h1(1, 2), h2(1, 2));
}