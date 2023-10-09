#include "graph/topological_sort.hpp"

#include <gtest/gtest.h>

testing::AssertionResult verify(const Graph& graph,
                                const std::vector<Graph::node_t>& order) {
    using node_t = Graph::node_t;
    const int n = graph.size();

    if (order.empty()) {
        return testing::AssertionFailure() << "`order` is empty.";
    }

    if (order.size() != n) {
        return testing::AssertionFailure()
               << "`order.size()` is " << order.size() << ", but expected " << n
               << ".";
    }

    std::vector<int> pos(n, -1);
    for (int i = 0; i < n; ++i) {
        node_t u = order[i];
        if (u < 0 || u >= n) {
            return testing::AssertionFailure()
                   << "`order` includes invalid node  " << u << ".";
        }
        if (pos[u] >= 0) {
            return testing::AssertionFailure()
                   << "Node " << u << " appears twice in `order`.";
        }
        pos[u] = i;
    }

    for (node_t u = 0; u < graph.size(); ++u) {
        for (auto&& v : graph.neighbors(u)) {
            if (pos[u] > pos[v]) {
                return testing::AssertionFailure()
                       << "Node " << v << " appears before node " << u << ".";
            }
        }
    }

    return testing::AssertionSuccess();
}

TEST(TopologicalSortTest, NoEdge) {
    Graph graph(3);
    std::vector<Graph::node_t> order = topological_sort(graph);
    EXPECT_TRUE(verify(graph, order));
}

TEST(TopologicalSortTest, Line) {
    Graph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 3);

    std::vector<Graph::node_t> order = topological_sort(graph);
    EXPECT_TRUE(verify(graph, order));
}

TEST(TopologicalSortTest, Cycle) {
    Graph graph(3);
    graph.add_edge(0, 1);
    graph.add_edge(1, 2);
    graph.add_edge(2, 0);

    std::vector<Graph::node_t> order = topological_sort(graph);
    EXPECT_TRUE(order.empty());
}

TEST(TopologicalSortTest, DAG) {
    Graph graph(5);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 4);
    graph.add_edge(2, 3);
    graph.add_edge(3, 4);

    std::vector<Graph::node_t> order = topological_sort(graph);
    EXPECT_TRUE(verify(graph, order));
}