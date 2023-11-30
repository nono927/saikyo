#include "convolution/or_convolution.hpp"

#include <gtest/gtest.h>

#include <vector>

TEST(OrConvolutionTest, Normal) {
    std::vector<int> A = {1, 3, 5, 7};
    std::vector<int> B = {2, 4, 6, 8};
    std::vector<int> expect = {2, 22, 46, 250};
    std::vector<int> actual = or_convolution(A, B);
    EXPECT_EQ(actual, expect);
}

TEST(OrConvolutionTest, NotPow2) {
    std::vector<int> A = {1, 3, 5, 7, 9};
    std::vector<int> B = {2, 4, 6, 8, 10};
    EXPECT_DEATH(or_convolution(A, B), "");
}

TEST(OrConvolutionTest, DifferentSize) {
    std::vector<int> A = {1, 3, 5, 7};
    std::vector<int> B = {2, 4};
    EXPECT_DEATH(or_convolution(A, B), "");
}
