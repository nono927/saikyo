#include "data_structure/convex_hull_trick.hpp"

#include <gtest/gtest.h>

using data_t = ConvexHullTrick::data_t;
using Lines = std::map<data_t, data_t>;

TEST(ConvexHullTrickTest, Empty) {
    ConvexHullTrick target;
    EXPECT_DEATH(target.argmin(42), "");
    EXPECT_DEATH(target.min(42), "");
}

TEST(ConvexHullTrickTest, AddConstSlope) {
    ConvexHullTrick target;

    target.add(1, 3);
    Lines expect0 = {{1, 3}};
    EXPECT_EQ(target.lines(), expect0);

    target.add(1, 4);
    EXPECT_EQ(target.lines(), expect0);

    target.add(1, 1);
    Lines expect1 = {{1, 1}};
    EXPECT_EQ(target.lines(), expect1);
}

TEST(ConvexHullTrickTest, AddUnnecessary) {
    ConvexHullTrick target;

    target.add(-1, 3);
    target.add(2, 3);
    Lines expect0 = {{-1, 3}, {2, 3}};
    EXPECT_EQ(target.lines(), expect0);

    target.add(1, 4);
    EXPECT_EQ(target.lines(), expect0);

    target.add(1, 2);
    Lines expect1 = {{-1, 3}, {1, 2}, {2, 3}};
    EXPECT_EQ(target.lines(), expect1);
}

TEST(ConvexHullTrickTest, AddAndDelete) {
    ConvexHullTrick target;

    target.add(-2, 2);
    target.add(-1, 1);
    target.add(1, 1);
    target.add(2, 2);
    Lines expect0 = {{-2, 2}, {-1, 1}, {1, 1}, {2, 2}};
    EXPECT_EQ(target.lines(), expect0);

    target.add(0, 0);
    Lines expect1 = {{-2, 2}, {0, 0}, {2, 2}};
    EXPECT_EQ(target.lines(), expect1);
}

TEST(ConvexHullTrickTest, Min) {
    ConvexHullTrick target;
    target.add(1, 3);
    std::pair<data_t, data_t> expect0 = {1, 3};
    EXPECT_EQ(target.argmin(4), expect0);
    EXPECT_EQ(target.min(4), 7);

    target.add(2, 2);
    target.add(-1, 6);
    Lines e = {{-1, 6}, {2, 2}, {1, 3}};
    EXPECT_EQ(target.lines(), e);
    std::pair<data_t, data_t> expect1 = {1, 3};
    EXPECT_EQ(target.argmin(1), expect1);
    EXPECT_EQ(target.min(1), 4);
}
