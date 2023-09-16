#include <gtest/gtest.h>

#include "vector/longest_increasing_subsequence.hpp"

TEST(LongestIncreasingSubsequenceTest, Increasing) {
    std::vector<long long> vec = {1, 2, 3, 4};
    std::vector<int> actual = longest_increasing_subsequence(vec);
    std::vector<int> expected = {1, 2, 3, 4};
    EXPECT_EQ(actual, expected);
}

TEST(LongestIncreasingSubsequenceTest, Same) {
    std::vector<long long> vec = {3, 3, 3, 3};
    std::vector<int> actual = longest_increasing_subsequence(vec);
    std::vector<int> expected = {1, 1, 1, 1};
    EXPECT_EQ(actual, expected);
}

TEST(LongestIncreasingSubsequenceTest, Normal) {
    std::vector<long long> vec = {1, 3, 4, 2, 3, 2, 5};
    std::vector<int> actual = longest_increasing_subsequence(vec);
    std::vector<int> expected = {1, 2, 3, 2, 3, 2, 4};
    EXPECT_EQ(actual, expected);
}