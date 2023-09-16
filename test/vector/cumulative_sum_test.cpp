#include <gtest/gtest.h>

#include "vector/cumulative_sum.hpp"

TEST(CumSumTest, One) {
    std::vector<long long> vec = {3};
    std::vector<long long> actual = cumsum(vec);
    std::vector<long long> expected = {0, 3};
    EXPECT_EQ(actual, expected);
}

TEST(CumSumTest, Normal) {
    std::vector<long long> vec = {1, 1, 1, 1};
    std::vector<long long> actual = cumsum(vec);
    std::vector<long long> expected = {0, 1, 2, 3, 4};
    EXPECT_EQ(actual, expected);
}

TEST(CumSum2dTest, One) {
    using Vector2d = std::vector<std::vector<long long>>;
    Vector2d vec2d = {{3}};
    Vector2d actual = cumsum2d(vec2d);
    Vector2d expected = {{0, 0}, {0, 3}};
    EXPECT_EQ(actual, expected);
}

TEST(CumSum2dTest, Normal) {
    using Vector2d = std::vector<std::vector<long long>>;
    Vector2d vec2d = {{1, 1, 1}, {1, 1, 1}};
    Vector2d actual = cumsum2d(vec2d);
    Vector2d expected = {{0, 0, 0, 0}, {0, 1, 2, 3}, {0, 2, 4, 6}};
    EXPECT_EQ(actual, expected);
}