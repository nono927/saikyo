#include "convolution/and_convolution.hpp"

#include <gtest/gtest.h>

#include <vector>

TEST(AndConvolutionTest, Normal) {
    std::vector<int> A = {1, 3, 5, 7};
    std::vector<int> B = {2, 4, 6, 8};
    std::vector<int> expect = {88, 64, 112, 56};
    std::vector<int> actual = and_convolution(A, B);
    EXPECT_EQ(actual, expect);
}

TEST(AndConvolutionTest, NotPow2) {
    std::vector<int> A = {1, 3, 5, 7, 9};
    std::vector<int> B = {2, 4, 6, 8, 10};
    EXPECT_DEATH(and_convolution(A, B), "");
}

TEST(AndConvolutionTest, DifferentSize) {
    std::vector<int> A = {1, 3, 5, 7};
    std::vector<int> B = {2, 4};
    EXPECT_DEATH(and_convolution(A, B), "");
}
