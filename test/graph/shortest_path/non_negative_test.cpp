#include "graph/shortest_path/non_negative.hpp"

#include <gtest/gtest.h>

using Distances = std::vector<WeightedGraph::weight_t>;
using Parents = std::vector<WeightedGraph::node_t>;

TEST(ShortestPathNonNegativeTest, One) {
    WeightedGraph graph(1);
    Distances expect_d = {0};
    Parents expect_p = {-1};
    auto [actual_d, actual_p] = shortest_path_non_negative(graph, 0);
    EXPECT_EQ(actual_d, expect_d);
    EXPECT_EQ(actual_p, expect_p);
}

TEST(ShortestPathNonNegativeTest, Tree) {
    WeightedGraph graph(4);
    graph.add_edge(0, 1, 3);
    graph.add_edge(1, 2, 1);
    graph.add_edge(1, 3, 4);
    Distances expect_d = {0, 3, 4, 7};
    Parents expect_p = {-1, 0, 1, 1};
    auto [actual_d, actual_p] = shortest_path_non_negative(graph, 0);
    EXPECT_EQ(actual_d, expect_d);
    EXPECT_EQ(actual_p, expect_p);
}

TEST(ShortestPathNonNegativeTest, Triangle) {
    WeightedGraph graph(3);
    graph.add_edge(0, 1, 3);
    graph.add_edge(1, 2, 1);
    graph.add_edge(0, 2, 5);
    Distances expect_d = {0, 3, 4};
    Parents expect_p = {-1, 0, 1};
    auto [actual_d, actual_p] = shortest_path_non_negative(graph, 0);
    EXPECT_EQ(actual_d, expect_d);
    EXPECT_EQ(actual_p, expect_p);
}

TEST(ShortestPathNonNegativeTest, StartFromNonZero) {
    WeightedGraph graph(3);
    graph.add_edge(0, 1, 3);
    graph.add_edge(1, 2, 1);
    graph.add_edge(0, 2, 5);
    Distances expect_d = {4611686018427387903LL, 0, 1};
    Parents expect_p = {-1, -1, 1};
    auto [actual_d, actual_p] = shortest_path_non_negative(graph, 1);
    EXPECT_EQ(actual_d, expect_d);
    EXPECT_EQ(actual_p, expect_p);
}

TEST(ShortestPathNonNegativeTest, Negative) {
    WeightedGraph graph(3);
    graph.add_edge(0, 1, 3);
    graph.add_edge(1, 2, -1);
    graph.add_edge(0, 2, 4);
    EXPECT_DEATH(shortest_path_non_negative(graph, 1), "");
}