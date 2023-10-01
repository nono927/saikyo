#pragma once

#include "./dfs.hpp"

// グラフに対して以下の操作を繰り返す．
// * 未探索な頂点のうち，頂点番号最小の点を選ぶ．選んだ点からDFSを行う．
//
// 最終的に，タプル
// (探索した頂点の順番, DFS木における各ノードの親)
// を返す．
//
// 同じ頂点から複数の辺が出ている場合は，先に追加した辺から順に探索する．
// 頂点 v が探索の始点の時，v の親は -1 とする．
std::tuple<std::vector<Graph::node_t>, std::vector<Graph::node_t>> dfs_all(
    const Graph& graph, const DfsType dfs_type = DfsType::PostOrder) {
    using node_t = Graph::node_t;

    const int n = graph.size();
    Graph graph_all(n + 1);
    for (node_t u = 0; u < n; ++u) {
        for (auto&& v : graph.neighbors(u)) {
            graph_all.add_edge(u, v);
        }
        graph_all.add_edge(n, u);
    }

    auto [order, parents] = dfs(graph_all, n, dfs_type);

    size_t sz_order = 0;
    for (auto&& u : order) {
        if (u < n) {
            order[sz_order++] = u;
        } else if (u > n && u < 2 * n + 1) {
            order[sz_order++] = u - 1;
        }
    }
    order.resize(sz_order);

    parents.pop_back();
    for (auto&& p : parents) {
        if (p == n) {
            p = -1;
        }
    }

    return {order, parents};
}