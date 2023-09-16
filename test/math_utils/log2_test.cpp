#include <gtest/gtest.h>

#include "math_utils/log2.hpp"

// ============================
// FloorLog2Test
// ============================

TEST(FloorLog2Test, One) {
    int result = floor_log2(1);
    EXPECT_EQ(result, 0);
}

TEST(FloorLog2Test, Pow2) {
    int result = floor_log2(16);
    EXPECT_EQ(result, 4);
}

TEST(FloorLog2Test, Pow2Minus1) {
    int result = floor_log2(15);
    EXPECT_EQ(result, 3);
}

TEST(FloorLog2Test, Large) {
    int result = floor_log2(1'000'000'000'000'000'000LL);
    EXPECT_EQ(result, 59);
}

// ============================
// CeilLog2Test
// ============================

TEST(CeilLog2Test, One) {
    int result = ceil_log2(1);
    EXPECT_EQ(result, 0);
}

TEST(CeilLog2Test, Pow2) {
    int result = ceil_log2(16);
    EXPECT_EQ(result, 4);
}

TEST(CeilLog2Test, Pow2Plus1) {
    int result = ceil_log2(17);
    EXPECT_EQ(result, 5);
}

TEST(CeilrLog2Test, Large) {
    int result = ceil_log2(1'000'000'000'000'000'000LL);
    EXPECT_EQ(result, 60);
}