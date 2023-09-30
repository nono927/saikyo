#include "graph/search/dfs.hpp"

#include <gtest/gtest.h>

#include "../testcase_generators.hpp"

// ================================
// DfsPreTest
// ================================

TEST(DfsPreTest, NoEdges) {
    Graph graph(3);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::PreOrder);

    std::vector<Graph::node_t> expected_order = {0};
    std::vector<Graph::node_t> expected_parents = {-1, -1, -1};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsPreTest, Line) {
    Graph graph = make_line_graph(4);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::PreOrder);

    std::vector<Graph::node_t> expected_order = {0, 1, 2, 3};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsPreTest, BinTree) {
    Graph graph = make_binary_tree(3);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::PreOrder);

    std::vector<Graph::node_t> expected_order = {0, 1, 3, 4, 2, 5, 6};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 0, 1, 1, 2, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsPreTest, Perfect) {
    Graph graph = make_perfect_graph(4);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::PreOrder);

    std::vector<Graph::node_t> expected_order = {0, 1, 2, 3};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

// ================================
// DfsPostTest
// ================================

TEST(DfsPostTest, NoEdges) {
    Graph graph(3);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::PostOrder);

    std::vector<Graph::node_t> expected_order = {0};
    std::vector<Graph::node_t> expected_parents = {-1, -1, -1};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsPostTest, Line) {
    Graph graph = make_line_graph(4);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::PostOrder);

    std::vector<Graph::node_t> expected_order = {3, 2, 1, 0};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsPostTest, BinTree) {
    Graph graph = make_binary_tree(3);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::PostOrder);

    std::vector<Graph::node_t> expected_order = {3, 4, 1, 5, 6, 2, 0};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 0, 1, 1, 2, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsPostTest, Perfect) {
    Graph graph = make_perfect_graph(4);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::PostOrder);

    std::vector<Graph::node_t> expected_order = {3, 2, 1, 0};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

// ================================
// DfsEulerTest
// ================================

TEST(DfsEulerTest, NoEdges) {
    Graph graph(3);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::Euler);

    std::vector<Graph::node_t> expected_order = {0, 3};
    std::vector<Graph::node_t> expected_parents = {-1, -1, -1};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsEulerTest, Line) {
    Graph graph = make_line_graph(4);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::Euler);

    std::vector<Graph::node_t> expected_order = {0, 1, 2, 3, 7, 6, 5, 4};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsEulerTest, BinTree) {
    Graph graph = make_binary_tree(3);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::Euler);

    std::vector<Graph::node_t> expected_order = {0, 1, 3,  10, 4,  11, 8,
                                                 2, 5, 12, 6,  13, 9,  7};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 0, 1, 1, 2, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}

TEST(DfsEulerTest, Perfect) {
    Graph graph = make_perfect_graph(4);
    auto [actual_order, actual_parents] = dfs(graph, 0, DfsType::Euler);

    std::vector<Graph::node_t> expected_order = {0, 1, 2, 3, 7, 6, 5, 4};
    std::vector<Graph::node_t> expected_parents = {-1, 0, 1, 2};
    EXPECT_EQ(actual_order, expected_order);
    EXPECT_EQ(actual_parents, expected_parents);
}