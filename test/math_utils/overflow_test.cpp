#include "math_utils/overflow.hpp"

#include <gtest/gtest.h>

#include <limits>

TEST(IsMulGreaterThanTest, Equal) {
    bool result = is_mul_greater_than(2, 3, 6);
    EXPECT_EQ(result, false);
}

TEST(IsMulGreaterThanTest, MaxTimesMaxGreaterThanMax) {
    long long M = std::numeric_limits<long long>::max();
    bool result = is_mul_greater_than(M, M, M);
    EXPECT_EQ(result, true);
}

TEST(IsMulGreaterThanTest, MinTimesMinGreaterThanMax) {
    long long M = std::numeric_limits<long long>::max();
    long long m = std::numeric_limits<long long>::min();
    bool result = is_mul_greater_than(m, m, M);
    EXPECT_EQ(result, true);
}

TEST(IsMulGreaterThanTest, MaxTimesMinLessThanMin) {
    long long M = std::numeric_limits<long long>::max();
    long long m = std::numeric_limits<long long>::min();
    bool result = is_mul_greater_than(M, m, m);
    EXPECT_EQ(result, false);
}