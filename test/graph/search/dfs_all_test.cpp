#include "graph/search/dfs_all.hpp"

#include <gtest/gtest.h>

TEST(DfsAllTest, PreOrder) {
    Graph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 0);
    graph.add_edge(2, 3);
    graph.add_edge(3, 2);

    auto [actual_order, actual_parents] = dfs_all(graph, DfsType::PreOrder);

    std::vector<Graph::node_t> expected_order = {0, 1, 2, 3};
    std::vector<Graph::node_t> expected_parents = {-1, 0, -1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsAllTest, PostOrder) {
    Graph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 0);
    graph.add_edge(2, 3);
    graph.add_edge(3, 2);

    auto [actual_order, actual_parents] = dfs_all(graph, DfsType::PostOrder);

    std::vector<Graph::node_t> expected_order = {1, 0, 3, 2};
    std::vector<Graph::node_t> expected_parents = {-1, 0, -1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsAllTest, Euler) {
    Graph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 0);
    graph.add_edge(2, 3);
    graph.add_edge(3, 2);

    auto [actual_order, actual_parents] = dfs_all(graph, DfsType::Euler);

    std::vector<Graph::node_t> expected_order = {0, 1, 5, 4, 2, 3, 7, 6};
    std::vector<Graph::node_t> expected_parents = {-1, 0, -1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}