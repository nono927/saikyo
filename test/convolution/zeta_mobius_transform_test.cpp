#include <gtest/gtest.h>

#include <vector>

#include "convolution/zeta_mobius_transform.hpp"

TEST(ZetaTransformTest, Pow2) {
    std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> expect = {1, 3, 4, 10, 6, 14, 16, 36};
    std::vector<int> actual = zeta_transform(input);
    EXPECT_EQ(actual, expect);
}

TEST(ZetaTransformTest, NotPow2) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    EXPECT_DEATH(zeta_transform(input), "");
}

TEST(MobiusTransformTest, Pow2) {
    std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> expect = {1, 1, 2, 0, 4, 0, 0, 0};
    std::vector<int> actual = mobius_transform(input);
    EXPECT_EQ(actual, expect);
}

TEST(MobiusTransformTest, NotPow2) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    EXPECT_DEATH(mobius_transform(input), "");
}