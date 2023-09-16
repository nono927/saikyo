#include "vector/run_length_encoding.hpp"

#include <gtest/gtest.h>

#include <string>
#include <vector>

TEST(RunLengthEncodingStringTest, Empty) {
    using Result = std::vector<std::pair<char, int>>;
    std::string S = "";
    Result actual = run_length_encoding(S);
    Result expected = {};
    EXPECT_EQ(actual, expected);
}

TEST(RunLengthEncodingStringTest, Normal) {
    using Result = std::vector<std::pair<char, int>>;
    std::string S = "aabccbbb";
    Result actual = run_length_encoding(S);
    Result expected = {{'a', 2}, {'b', 1}, {'c', 2}, {'b', 3}};
    EXPECT_EQ(actual, expected);
}

TEST(RunLengthEncodingStringTest, Same) {
    using Result = std::vector<std::pair<char, int>>;
    std::string S = "aaaaaaa";
    Result actual = run_length_encoding(S);
    Result expected = {{'a', 7}};
    EXPECT_EQ(actual, expected);
}

TEST(RunLengthEncodingStringTest, Distinct) {
    using Result = std::vector<std::pair<char, int>>;
    std::string S = "abcde";
    Result actual = run_length_encoding(S);
    Result expected = {{'a', 1}, {'b', 1}, {'c', 1}, {'d', 1}, {'e', 1}};
    EXPECT_EQ(actual, expected);
}

TEST(RunLengthEncodingVectorTest, Empty) {
    using Result = std::vector<std::pair<long long, int>>;
    std::vector<long long> V = {};
    Result actual = run_length_encoding(V);
    Result expected = {};
    EXPECT_EQ(actual, expected);
}

TEST(RunLengthEncodingVectorTest, Normal) {
    using Result = std::vector<std::pair<long long, int>>;
    std::vector<long long> V = {1, 1, 2, 3, 3, 2, 2, 2};
    Result actual = run_length_encoding(V);
    Result expected = {{1, 2}, {2, 1}, {3, 2}, {2, 3}};
    EXPECT_EQ(actual, expected);
}

TEST(RunLengthEncodingVectorTest, Same) {
    using Result = std::vector<std::pair<long long, int>>;
    std::vector<long long> V = {1, 1, 1, 1, 1, 1, 1};
    Result actual = run_length_encoding(V);
    Result expected = {{1, 7}};
    EXPECT_EQ(actual, expected);
}

TEST(RunLengthEncodingVectorTest, Distinct) {
    using Result = std::vector<std::pair<long long, int>>;
    std::vector<long long> V = {1, 2, 3, 4, 5};
    Result actual = run_length_encoding(V);
    Result expected = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}};
    EXPECT_EQ(actual, expected);
}