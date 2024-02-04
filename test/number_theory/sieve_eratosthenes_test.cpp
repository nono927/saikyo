#include "number_theory/sieve_eratosthenes.hpp"

#include <gtest/gtest.h>

TEST(SieveTest, Sieve) {
    std::vector<bool> actual = sieve_eratosthenes(8);
    std::vector<bool> expect = {false, false, true,  true,
                                false, true,  false, true};
    EXPECT_EQ(actual, expect);
}