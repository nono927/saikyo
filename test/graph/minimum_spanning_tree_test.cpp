#include "graph/minimum_spanning_tree.hpp"

#include <gtest/gtest.h>

using weight_t = WeightedGraph::weight_t;

TEST(MinimumSpanningTreeTest, Tree) {
    WeightedGraph graph(4);
    graph.add_edge(0, 1, 3);
    graph.add_edge(1, 0, 3);
    graph.add_edge(1, 2, 1);
    graph.add_edge(2, 1, 1);
    graph.add_edge(1, 3, 4);
    graph.add_edge(3, 1, 4);
    weight_t expect = 8;
    weight_t actual = minimum_spanning_tree(graph);
    EXPECT_EQ(actual, expect);
}

TEST(MinimumSpanningTreeTest, Triangle) {
    WeightedGraph graph(3);
    graph.add_edge(0, 1, 3);
    graph.add_edge(1, 0, 3);
    graph.add_edge(0, 2, 1);
    graph.add_edge(2, 0, 1);
    graph.add_edge(1, 2, 4);
    graph.add_edge(2, 1, 4);
    weight_t expect = 4;
    weight_t actual = minimum_spanning_tree(graph);
    EXPECT_EQ(actual, expect);
}

TEST(MinimumSpanningTreeTest, One) {
    WeightedGraph graph(1);
    weight_t expect = 0;
    weight_t actual = minimum_spanning_tree(graph);
    EXPECT_EQ(actual, expect);
}

TEST(MinimumSpanningTreeTest, DisConnected) {
    WeightedGraph graph(4);
    graph.add_edge(0, 1, 3);
    graph.add_edge(1, 0, 3);
    graph.add_edge(2, 3, 1);
    graph.add_edge(3, 2, 1);
    weight_t expect = 4611686018427387903LL;
    weight_t actual = minimum_spanning_tree(graph);
    EXPECT_EQ(actual, expect);
}