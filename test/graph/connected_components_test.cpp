#include "graph/connected_components.hpp"

#include <gtest/gtest.h>

using node_t = Graph::node_t;

// 出力結果から元のグラフを復元する．
Graph reconstruct(
    const int num_node,
    const std::vector<std::pair<std::vector<node_t>, Graph>>& result) {
    Graph graph(num_node);
    for (auto&& [ids, subgraph] : result) {
        const int m = subgraph.size();
        for (node_t i = 0; i < m; ++i) {
            node_t u = ids[i];
            for (auto&& j : subgraph.neighbors(i)) {
                node_t v = ids[j];
                graph.add_edge(u, v);
            }
        }
    }
    return graph;
}

// 各連結成分のサイズをチェックする．
testing::AssertionResult check_size(
    const std::vector<std::pair<std::vector<node_t>, Graph>>& result) {
    for (auto&& [ids, subgraph] : result) {
        if ((int)ids.size() != subgraph.size()) {
            return testing::AssertionFailure()
                   << "Expected: ids.size() == subgraph.size"
                   << ", actual: " << ids.size() << " != " << subgraph.size();
        }
        if (subgraph.size() == 0) {
            return testing::AssertionFailure()
                   << "The result contains an empty subgraph";
        }
    }
    return testing::AssertionSuccess();
}

// 頂点idの範囲が適切かどうかをチェックする．
testing::AssertionResult check_range(
    const int num_node,
    const std::vector<std::pair<std::vector<node_t>, Graph>>& result) {
    for (auto&& [ids, subgraph] : result) {
        for (auto&& u : ids) {
            if (u < 0 || u >= num_node) {
                return testing::AssertionFailure()
                       << "Expected: 0 <= u < " << num_node
                       << ", actual: u = " << u;
            }
        }

        const int m = subgraph.size();
        for (node_t i = 0; i < m; ++i) {
            for (auto&& j : subgraph.neighbors(i)) {
                if (j < 0 || j >= m) {
                    return testing::AssertionFailure()
                           << "Expected: 0 <= j < " << m
                           << ", actual: j = " << j;
                }
            }
        }
    }

    return testing::AssertionSuccess();
}

// 各頂点がちょうど1回だけ現れることをチェックする．
testing::AssertionResult check_independent(
    const int num_node,
    const std::vector<std::pair<std::vector<node_t>, Graph>>& result) {
    std::vector<int> cnt(num_node);
    for (auto&& [ids, subgraph] : result) {
        for (auto&& u : ids) {
            ++cnt[u];
        }
    }

    for (int i = 0; i < num_node; ++i) {
        if (cnt[i] == 0) {
            return testing::AssertionFailure()
                   << "The result does not contain vertex " << i;
        }
        if (cnt[i] > 1) {
            return testing::AssertionFailure()
                   << "Vertex " << i << " appears " << cnt[i] << " times";
        }
    }

    return testing::AssertionSuccess();
}

// 2つのグラフが辺の順番を除いて等しいことをチェックする．
testing::AssertionResult check_graph(const Graph& actual, const Graph& expect) {
    std::vector<std::vector<node_t>> actual_neighbors(actual._neighbors);
    std::vector<std::vector<node_t>> expect_neighbors(expect._neighbors);
    for (auto&& v : actual_neighbors) {
        std::sort(v.begin(), v.end());
    }
    for (auto&& v : expect_neighbors) {
        std::sort(v.begin(), v.end());
    }
    if (actual_neighbors != expect_neighbors) {
        return testing::AssertionFailure() << "actual != expect";
    }

    return testing::AssertionSuccess();
}

TEST(ConnectedComponentsTest, Connected) {
    const int n = 2;
    Graph graph(n);
    graph.add_edge(0, 1);

    auto result = connected_components(graph);
    ASSERT_EQ(result.size(), 1);
    check_size(result);
    check_range(n, result);
    check_independent(n, result);
    auto actual = reconstruct(n, result);
    check_graph(actual, graph);
}

TEST(ConnectedComponentsTest, NoEdges) {
    const int n = 3;
    Graph graph(n);

    auto result = connected_components(graph);
    ASSERT_EQ(result.size(), 3);
    check_size(result);
    check_range(n, result);
    check_independent(n, result);
    auto actual = reconstruct(n, result);
    check_graph(actual, graph);
}

TEST(ConnectedComponentsTest, DisConnected) {
    const int n = 5;
    Graph graph(n);
    graph.add_edge(0, 1);
    graph.add_edge(1, 3);
    graph.add_edge(3, 0);
    graph.add_edge(2, 4);

    auto result = connected_components(graph);
    ASSERT_EQ(result.size(), 2);
    check_size(result);
    check_range(n, result);
    check_independent(n, result);
    auto actual = reconstruct(n, result);
    check_graph(actual, graph);
}
