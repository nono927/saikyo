#pragma once

#include <queue>
#include <tuple>

#include "../weighted_graph.hpp"

// 一般の重み付きグラフに対して，タプル
// (始点から各ノードまでの最短距離, 最短経路木における各ノードの親)
// を返す．
//
// 到達していない頂点までの距離は無限とする．
// 探索の始点，または到達していない頂点の親は-1とする．
std::tuple<std::vector<WeightedGraph::weight_t>,
           std::vector<WeightedGraph::node_t>>
shortest_path_general(const WeightedGraph& graph,
                      WeightedGraph::node_t source) {
    using node_t = WeightedGraph::node_t;
    using weight_t = WeightedGraph::weight_t;
    constexpr weight_t INFTY = std::numeric_limits<weight_t>::max() / 2;

    const int n = graph.size();
    std::vector<weight_t> distances(n, INFTY);
    std::vector<node_t> parents(n, -1);
    distances[source] = 0;

    std::queue<node_t> que;
    std::vector<bool> in_queue(n);
    std::vector<int> count(n);
    que.emplace(source);
    in_queue[source] = true;
    ++count[source];
    while (!que.empty()) {
        auto v = que.front();
        que.pop();
        in_queue[v] = false;
        for (auto&& [to, weight] : graph.neighbors(v)) {
            auto dist_to = distances[v] + weight;
            if (distances[to] <= dist_to) {
                continue;
            }
            distances[to] = dist_to;
            parents[to] = v;
            if (!in_queue[to]) {
                if (++count[to] >= graph.size()) {
                    return {{}, {}};
                }
                que.emplace(to);
                in_queue[to] = true;
            }
        }
    }

    return {distances, parents};
}