#include "data_structure/sorted_array.hpp"

#include <gtest/gtest.h>

#include <functional>

TEST(SortedArrayTest, Init) {
    SortedArray<int> sorted_array(1);
    EXPECT_EQ(sorted_array.size(), 0);
    EXPECT_EQ(sorted_array.capacity(), 1);
    EXPECT_DEATH(SortedArray<int>(0), "");
}

TEST(SortedArrayTest, InsertOne) {
    SortedArray<int> sorted_array(1);
    sorted_array.insert(3);
    EXPECT_EQ(sorted_array.size(), 1);
    EXPECT_EQ(sorted_array.capacity(), 1);
    EXPECT_EQ(sorted_array[0], 3);
    EXPECT_DEATH(sorted_array[1], "");
}

TEST(SortedArrayTest, AscendingOrder) {
    SortedArray<int> sorted_array(2);

    sorted_array.insert(2);
    EXPECT_EQ(sorted_array.size(), 1);
    EXPECT_EQ(sorted_array[0], 2);

    sorted_array.insert(3);
    EXPECT_EQ(sorted_array.size(), 2);
    EXPECT_EQ(sorted_array[0], 2);
    EXPECT_EQ(sorted_array[1], 3);

    sorted_array.insert(1);
    EXPECT_EQ(sorted_array.size(), 2);
    EXPECT_EQ(sorted_array[0], 1);
    EXPECT_EQ(sorted_array[1], 2);
}

TEST(SortedArrayTest, DescendingOrder) {
    SortedArray<int, std::greater<int>> sorted_array(2);

    sorted_array.insert(2);
    EXPECT_EQ(sorted_array.size(), 1);
    EXPECT_EQ(sorted_array[0], 2);

    sorted_array.insert(3);
    EXPECT_EQ(sorted_array.size(), 2);
    EXPECT_EQ(sorted_array[0], 3);
    EXPECT_EQ(sorted_array[1], 2);

    sorted_array.insert(1);
    EXPECT_EQ(sorted_array.size(), 2);
    EXPECT_EQ(sorted_array[0], 3);
    EXPECT_EQ(sorted_array[1], 2);
}