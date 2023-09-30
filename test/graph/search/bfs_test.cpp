#include "graph/search/bfs.hpp"

#include <gtest/gtest.h>

#include "../testcase_generators.hpp"

TEST(BfsTest, NoEdges) {
    Graph graph(3);
    auto [actual_order, actual_parents] = bfs(graph, 0);

    std::vector<Graph::node_t> expected_order = {0};
    std::vector<Graph::node_t> expected_parents = {-1, -1, -1};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(BfsTest, Line) {
    Graph graph = make_line_graph(4);
    auto [actual_order, actual_parents] = bfs(graph, 0);

    std::vector<Graph::node_t> expected_order = {0, 1, 2, 3};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(BfsTest, BinTree) {
    Graph graph = make_binary_tree(3);
    auto [actual_order, actual_parents] = bfs(graph, 0);

    std::vector<Graph::node_t> expected_order = {0, 1, 2, 3, 4, 5, 6};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 0, 1, 1, 2, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(BfsTest, Perfect) {
    Graph graph = make_perfect_graph(4);
    auto [actual_order, actual_parents] = bfs(graph, 0);

    std::vector<Graph::node_t> expected_order = {0, 1, 2, 3};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 0, 0};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}