#include "graph/to_bipartite_graph.hpp"

#include <gtest/gtest.h>

#include <atcoder/dsu>

#include "./testcase_generators.hpp"

testing::AssertionResult verify(const Graph& graph,
                                const std::vector<int>& labels) {
    using node_t = Graph::node_t;
    const int n = graph.size();

    auto msg_label = [&](node_t v) {
        std::ostringstream oss;
        oss << "labels[" << v << "]";
        return oss.str();
    };

    auto msg_two_labels = [&](node_t u, node_t v) {
        std::ostringstream oss;
        oss << "(" << msg_label(u) << " = " << labels[u] << ", " << msg_label(v)
            << " = " << labels[v] << ")";
        return oss.str();
    };

    auto failure_connected = [&](node_t u, node_t v) {
        std::ostringstream oss;
        return testing::AssertionFailure()
               << "Node " << u << " and " << v << " are connected, but "
               << msg_label(u) << " / 2 != " << msg_label(v) << " / 2 "
               << msg_two_labels(u, v) << ".";
    };

    auto failure_disconnected = [&](node_t u, node_t v) {
        return testing::AssertionFailure()
               << "Node " << u << " and " << v << " are disconnected, but "
               << msg_label(u) << " / 2 == " << msg_label(v) << " / 2 "
               << msg_two_labels(u, v) << ".";
    };

    auto failure_adjacent = [&](node_t u, node_t v) {
        return testing::AssertionFailure()
               << "Node " << u << " and " << v << " are adjacent, but "
               << msg_label(u) << " == " << msg_label(v) << " "
               << msg_two_labels(u, v) << ".";
    };

    atcoder::dsu uf(n);
    for (node_t u = 0; u < graph.size(); ++u) {
        for (auto&& v : graph.neighbors(u)) {
            if (labels[u] / 2 != labels[v] / 2) {
                return failure_connected(u, v);
            }
            if (labels[u] == labels[v]) {
                return failure_adjacent(u, v);
            }
            uf.merge(u, v);
        }
    }

    for (node_t u = 0; u < n - 1; ++u) {
        for (node_t v = u + 1; v < n; ++v) {
            if (uf.same(u, v) & (labels[u] / 2 != labels[v] / 2)) {
                return failure_connected(u, v);
            }
            if (!uf.same(u, v) & (labels[u] / 2 == labels[v] / 2)) {
                return failure_disconnected(u, v);
            }
        }
    }

    return testing::AssertionSuccess();
}

TEST(ToBipartiteGraphTest, NoEdge) {
    Graph graph(3);
    std::vector<Graph::node_t> labels = to_bipartite_graph(graph);
    EXPECT_TRUE(verify(graph, labels));
}

TEST(ToBipartiteGraphTest, Line) {
    Graph graph = make_line_graph(4);
    std::vector<Graph::node_t> labels = to_bipartite_graph(graph);
    EXPECT_TRUE(verify(graph, labels));
}

TEST(ToBipartiteGraphTest, Triangle) {
    Graph graph = make_perfect_graph(3);
    std::vector<Graph::node_t> labels = to_bipartite_graph(graph);
    EXPECT_TRUE(labels.empty());
}

TEST(ToBipartiteGraphTest, TwoLines) {
    Graph graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(1, 0);
    graph.add_edge(2, 3);
    graph.add_edge(3, 2);

    std::vector<Graph::node_t> labels = to_bipartite_graph(graph);
    EXPECT_TRUE(verify(graph, labels));
}