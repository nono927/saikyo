#include "graph/tree/diameter.hpp"

#include <gtest/gtest.h>

#include "../testcase_generators.hpp"

TEST(DiameterTest, Line) {
    Graph graph = make_line_graph(4);
    auto [d, u, v] = tree_diameter(graph);
    EXPECT_EQ(d, 3);
    EXPECT_EQ(u, 3);
    EXPECT_EQ(v, 0);
}

TEST(DiameterTest, BinTree) {
    Graph graph = make_binary_tree(3);
    auto [d, u, v] = tree_diameter(graph);
    EXPECT_EQ(d, 4);
    EXPECT_EQ(u, 3);
    EXPECT_EQ(v, 5);
}