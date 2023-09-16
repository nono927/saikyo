#include "math_utils/digits.hpp"

#include <gtest/gtest.h>

TEST(DigitsTest, DigitsStringToVector) {
    std::string S = "123";
    std::vector<long long> actual = digits_string_to_vector(S);
    std::vector<long long> expected = {1, 2, 3};
    EXPECT_EQ(actual, expected);
}

TEST(DigitsTest, DigitsVectorToString) {
    std::vector<long long> V = {1, 2, 3};
    std::string actual = digits_vector_to_string(V);
    std::string expected = "123";
    EXPECT_EQ(actual, expected);
}