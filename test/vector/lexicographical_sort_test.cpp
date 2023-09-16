#include "vector/lexicographical_sort.hpp"

#include <gtest/gtest.h>

#include <vector>

TEST(LexicographicalSortTest, Two) {
    std::vector<long long> v1 = {2, 1, 2};
    std::vector<char> v2 = {'a', 'b', 'c'};
    lexicographical_sort(v1, v2);

    std::vector<long long> expected_v1 = {1, 2, 2};
    std::vector<char> expected_v2 = {'b', 'a', 'c'};
    EXPECT_EQ(v1, expected_v1);
    EXPECT_EQ(v2, expected_v2);
}

TEST(LexicographicalSortTest, Three) {
    std::vector<long long> v1 = {2, 1, 2, 2};
    std::vector<char> v2 = {'a', 'b', 'c', 'a'};
    std::vector<long long> v3 = {100, 101, 102, 103};
    lexicographical_sort(v1, v2, v3);

    std::vector<long long> expected_v1 = {1, 2, 2, 2};
    std::vector<char> expected_v2 = {'b', 'a', 'a', 'c'};
    std::vector<long long> expected_v3 = {101, 100, 103, 102};
    EXPECT_EQ(v1, expected_v1);
    EXPECT_EQ(v2, expected_v2);
    EXPECT_EQ(v3, expected_v3);
}