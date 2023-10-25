#include "number_theory/prime_factorization.hpp"

#include <gtest/gtest.h>

#include <utility>
#include <vector>

TEST(PrimeFactorizationTest, One) {
    std::vector<std::pair<long long, int>> actual = prime_factorization(1);
    std::vector<std::pair<long long, int>> expected = {};
    EXPECT_EQ(actual, expected);
}

TEST(PrimeFactorizationTest, Prime) {
    std::vector<std::pair<long long, int>> actual = prime_factorization(13);
    std::vector<std::pair<long long, int>> expected = {{13, 1}};
    EXPECT_EQ(actual, expected);
}

TEST(PrimeFactorizationTest, Square) {
    std::vector<std::pair<long long, int>> actual = prime_factorization(16);
    std::vector<std::pair<long long, int>> expected = {{2, 4}};
    EXPECT_EQ(actual, expected);
}

TEST(PrimeFactorizationTest, HighlyCompositeNumber) {
    std::vector<std::pair<ll, int>> actual = prime_factorization(24);
    std::vector<std::pair<ll, int>> expected = {{2, 3}, {3, 1}};
    EXPECT_EQ(actual, expected);
}

TEST(PrimeFactorizationTest, LargePrime) {
    std::vector<std::pair<long long, int>> actual = prime_factorization(200560490131);
    std::vector<std::pair<long long, int>> expected = {{200560490131, 1}};
    EXPECT_EQ(actual, expected);
}