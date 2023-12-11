#include "graph/shortest_path/unweighted.hpp"

#include <gtest/gtest.h>

using Distances = std::vector<long long>;
using Parents = std::vector<Graph::node_t>;

TEST(ShortestPathUnweightedTest, One) {
    Graph graph(1);
    Distances expect_d = {0};
    Parents expect_p = {-1};
    auto [actual_d, actual_p] = shortest_path_unweighted(graph, 0);
    EXPECT_EQ(actual_d, expect_d);
    EXPECT_EQ(actual_p, expect_p);
}

TEST(ShortestPathUnweightedTest, Tree) {
    Graph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(1, 3);
    Distances expect_d = {0, 1, 2, 2};
    Parents expect_p = {-1, 0, 1, 1};
    auto [actual_d, actual_p] = shortest_path_unweighted(graph, 0);
    EXPECT_EQ(actual_d, expect_d);
    EXPECT_EQ(actual_p, expect_p);
}

TEST(ShortestPathUnweightedTest, Triangle) {
    Graph graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(0, 2);
    Distances expect_d = {0, 1, 1};
    Parents expect_p = {-1, 0, 0};
    auto [actual_d, actual_p] = shortest_path_unweighted(graph, 0);
    EXPECT_EQ(actual_d, expect_d);
    EXPECT_EQ(actual_p, expect_p);
}

TEST(ShortestPathUnweightedTest, StartFromNonZero) {
    Graph graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(0, 2);
    Distances expect_d = {4611686018427387903LL, 0, 1};
    Parents expect_p = {-1, -1, 1};
    auto [actual_d, actual_p] = shortest_path_unweighted(graph, 1);
    EXPECT_EQ(actual_d, expect_d);
    EXPECT_EQ(actual_p, expect_p);
}