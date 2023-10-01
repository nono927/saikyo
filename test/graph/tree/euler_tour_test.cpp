#include "graph/tree/euler_tour.hpp"

#include <gtest/gtest.h>

#include "../testcase_generators.hpp"

TEST(EulerTourTest, Line) {
    Graph graph = make_line_graph(4);
    auto [actual_tin, actual_tout] = euler_tour(graph, 0);

    std::vector<Graph::node_t> expected_tin = {0, 1, 2, 3};
    std::vector<Graph::node_t> expected_tout = {7, 6, 5, 4};
    EXPECT_EQ(actual_tin, expected_tin);
    EXPECT_EQ(actual_tout, expected_tout);
}

TEST(EulerTourTest, BinTree) {
    Graph graph = make_binary_tree(3);
    auto [actual_tin, actual_tout] = euler_tour(graph, 0);

    std::vector<Graph::node_t> expected_tin = {0, 1, 7, 2, 4, 8, 10};
    std::vector<Graph::node_t> expected_tout = {13, 6, 12, 3, 5, 9, 11};
    EXPECT_EQ(actual_tin, expected_tin);
    EXPECT_EQ(actual_tout, expected_tout);
}
