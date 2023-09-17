#include "data_structure/doubling.hpp"

#include <gtest/gtest.h>

#include <vector>

TEST(DoublingTest, NonPositiveMaxNumSteps) {
    std::vector<long long> nexts = {0, 0, 0};
    EXPECT_DEATH(Doubling<>(nexts, 0), "");
}

TEST(DoublingTest, DoNothing) {
    std::vector<long long> nexts = {0, 0, 0};
    Doubling<long long> doubling(nexts, 1);
    EXPECT_EQ(doubling.step(0, 0), 0);
    EXPECT_EQ(doubling.step(1, 0), 1);
    EXPECT_EQ(doubling.step(2, 0), 2);
}

TEST(DoublingTest, NegativeNumSteps) {
    std::vector<long long> nexts = {0, 0, 0};
    Doubling<long long> doubling(nexts, 1);
    EXPECT_DEATH(doubling.step(0, -1), "");
}

TEST(DoublingTest, Identity) {
    std::vector<long long> nexts = {0, 1, 2};
    Doubling<long long> doubling(nexts, 1'000'000);
    EXPECT_EQ(doubling.step(0, 1), 0);
    EXPECT_EQ(doubling.step(0, 3), 0);
    EXPECT_EQ(doubling.step(0, 4), 0);
    EXPECT_EQ(doubling.step(0, 1'000'000), 0);
    EXPECT_EQ(doubling.step(1, 13), 1);
    EXPECT_EQ(doubling.step(2, 16), 2);
}

TEST(DoublingTest, Line) {
    std::vector<long long> nexts = {1, 2, 3, -1};
    Doubling<long long> doubling(nexts, 4);
    EXPECT_EQ(doubling.step(0, 1), 1);
    EXPECT_EQ(doubling.step(0, 2), 2);
    EXPECT_EQ(doubling.step(0, 3), 3);
    EXPECT_EQ(doubling.step(0, 4), -1);
    EXPECT_EQ(doubling.step(1, 1), 2);
    EXPECT_EQ(doubling.step(1, 2), 3);
    EXPECT_EQ(doubling.step(1, 3), -1);
    EXPECT_EQ(doubling.step(2, 1), 3);
    EXPECT_EQ(doubling.step(2, 2), -1);
    EXPECT_EQ(doubling.step(3, 1), -1);
}

TEST(DoublingTest, Cycle) {
    std::vector<long long> nexts = {1, 2, 3, 0};
    Doubling<long long> doubling(nexts, 1'000'000'000'000'000'000);
    EXPECT_EQ(doubling.step(0, 1), 1);
    EXPECT_EQ(doubling.step(0, 3), 3);
    EXPECT_EQ(doubling.step(0, 6), 2);
    EXPECT_EQ(doubling.step(0, 999'999'999'999'999'999), 3);
    EXPECT_EQ(doubling.step(0, 1'000'000'000'000'000'000), 0);
}

TEST(DoublingTest, BinaryTree) {
    std::vector<long long> nexts = {-1, 0, 0, 1, 1, 2, 2};
    Doubling<long long> doubling(nexts, 2);
    EXPECT_EQ(doubling.step(3, 1), 1);
    EXPECT_EQ(doubling.step(3, 2), 0);
    EXPECT_EQ(doubling.step(4, 1), 1);
    EXPECT_EQ(doubling.step(4, 2), 0);
    EXPECT_EQ(doubling.step(5, 1), 2);
    EXPECT_EQ(doubling.step(5, 2), 0);
    EXPECT_EQ(doubling.step(6, 1), 2);
    EXPECT_EQ(doubling.step(6, 2), 0);
}