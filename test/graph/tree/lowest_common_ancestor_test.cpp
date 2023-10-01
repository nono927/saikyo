#include "graph/tree/lowest_common_ancestor.hpp"

#include <gtest/gtest.h>

#include "../testcase_generators.hpp"

TEST(LowestCommonAncestorTest, Parent) {
    Graph graph = make_binary_tree(3);
    LowestCommonAncestor lca(graph, 0);
    EXPECT_EQ(lca.parent(1, 1), 0);
    EXPECT_EQ(lca.parent(3, 1), 1);
    EXPECT_EQ(lca.parent(3, 2), 0);
    EXPECT_EQ(lca.parent(6, 1), 2);
    EXPECT_EQ(lca.parent(6, 2), 0);
    EXPECT_EQ(lca.parent(6, 3), -1);
}

TEST(LowestCommonAncestorTest, Lca) {
    Graph graph = make_binary_tree(3);
    LowestCommonAncestor lca(graph, 0);
    EXPECT_EQ(lca.lca(1, 1), 1);
    EXPECT_EQ(lca.lca(1, 3), 1);
    EXPECT_EQ(lca.lca(1, 2), 0);
    EXPECT_EQ(lca.lca(1, 6), 0);
    EXPECT_EQ(lca.lca(3, 4), 1);
    EXPECT_EQ(lca.lca(3, 6), 0);
    EXPECT_EQ(lca.lca(5, 6), 2);
}

TEST(LowestCommonAncestorTest, Distance) {
    Graph graph = make_binary_tree(3);
    LowestCommonAncestor lca(graph, 0);
    EXPECT_EQ(lca.distance(1, 1), 0);
    EXPECT_EQ(lca.distance(1, 3), 1);
    EXPECT_EQ(lca.distance(1, 2), 2);
    EXPECT_EQ(lca.distance(1, 6), 3);
    EXPECT_EQ(lca.distance(3, 4), 2);
    EXPECT_EQ(lca.distance(3, 6), 4);
    EXPECT_EQ(lca.distance(5, 6), 2);
}

TEST(LowestCommonAncestorTest, IsOnPath) {
    Graph graph = make_binary_tree(3);
    LowestCommonAncestor lca(graph, 0);
    EXPECT_EQ(lca.is_on_path(1, 3, 6), true);
    EXPECT_EQ(lca.is_on_path(4, 3, 6), false);
}
