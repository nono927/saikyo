#pragma once

#include <tuple>
#include <vector>

#include "graph/graph.hpp"
#include "graph/search/bfs.hpp"

using ll = long long;

// 重みなしグラフに対して，タプル
// (始点から各ノードまでの最短のパスの長さ, 最短経路木における各ノードの親)
// を返す．
//
// 到達していない頂点までの距離は無限とする．
// 探索の始点，または到達していない頂点の親は-1とする．
std::tuple<std::vector<ll>, std::vector<Graph::node_t>>
shortest_path_unweighted(const Graph& graph, const Graph::node_t source) {
    auto [order, parents] = bfs(graph, source);
    constexpr ll LL_INFTY = std::numeric_limits<ll>::max() / 2;
    std::vector<ll> dists(graph.size(), LL_INFTY);
    dists[source] = 0;
    for (auto&& u : order) {
        auto p = parents[u];
        if (p < 0 || dists[p] == LL_INFTY) continue;
        dists[u] = dists[p] + 1;
    }
    return {dists, parents};
}