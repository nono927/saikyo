#pragma once

#include <cassert>
#include <limits>
#include <queue>
#include <tuple>
#include <utility>

#include "./weighted_graph.hpp"

// 辺の重みが非負であるグラフに対して，タプル
// (始点から各ノードまでの最短距離, 最短経路木における各ノードの親)
// を返す．
//
// 到達していない頂点までの距離は無限とする．
// 探索の始点，または到達していない頂点の親は-1とする．
std::tuple<std::vector<WeightedGraph::weight_t>,
           std::vector<WeightedGraph::node_t>>
shortest_path_non_negative(const WeightedGraph& graph,
                           WeightedGraph::node_t source) {
    using node_t = WeightedGraph::node_t;
    using weight_t = WeightedGraph::weight_t;
    constexpr weight_t INFTY = std::numeric_limits<weight_t>::max() / 2;

    const int n = graph.size();
    std::vector<weight_t> distances(n, INFTY);
    std::vector<node_t> parents(n, -1);
    distances[source] = 0;

    using r_edge_t = std::pair<weight_t, node_t>;
    std::priority_queue<r_edge_t, std::vector<r_edge_t>, std::greater<r_edge_t>>
        heap;
    heap.emplace(0, source);
    while (!heap.empty()) {
        auto [dist, v] = heap.top();
        heap.pop();
        if (distances[v] != dist) {
            continue;
        }
        for (auto [to, weight] : graph.neighbors(v)) {
            assert(weight >= 0);
            auto dist_to = dist + weight;
            if (distances[to] <= dist_to) {
                continue;
            }
            distances[to] = dist_to;
            parents[to] = v;
            heap.emplace(dist_to, to);
        }
    }

    return {distances, parents};
}