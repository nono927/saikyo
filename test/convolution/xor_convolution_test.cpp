#include "convolution/xor_convolution.hpp"

#include <gtest/gtest.h>

#include <vector>

TEST(XorConvolutionTest, Normal) {
    std::vector<int> A = {1, 3, 5, 7};
    std::vector<int> B = {2, 4, 6, 8};
    std::vector<int> expect = {100, 92, 68, 60};
    std::vector<int> actual = xor_convolution(A, B);
    EXPECT_EQ(actual, expect);
}

TEST(XorConvolutionTest, NotPow2) {
    std::vector<int> A = {1, 3, 5, 7, 9};
    std::vector<int> B = {2, 4, 6, 8, 10};
    EXPECT_DEATH(xor_convolution(A, B), "");
}

TEST(XorConvolutionTest, DifferentSize) {
    std::vector<int> A = {1, 3, 5, 7};
    std::vector<int> B = {2, 4};
    EXPECT_DEATH(xor_convolution(A, B), "");
}
