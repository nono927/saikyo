#pragma once

#include <queue>
#include <tuple>
#include <vector>

#include "../graph.hpp"

// グラフに対してBFSを行い，タプル
// (探索した頂点の順番, BFS木における各ノードの親)
// を返す．
//
// 同じ頂点から複数の辺が出ている場合は，先に追加した辺から順に探索する．
// 頂点 v が探索の始点，または到達しなかった頂点の時，v の親は -1 とする．
std::tuple<std::vector<Graph::node_t>, std::vector<Graph::node_t>> bfs(
    const Graph& graph, const Graph::node_t source) {
    using node_t = Graph::node_t;

    const int n = graph.size();
    std::vector<node_t> order;
    std::vector<node_t> parents(n, -1);

    std::queue<node_t> que;
    std::vector<bool> used(n);
    que.push(source);
    used[source] = true;
    while (!que.empty()) {
        node_t v = que.front();
        que.pop();
        order.push_back(v);

        for (auto&& w : graph.neighbors(v)) {
            if (!used[w]) {
                used[w] = true;
                parents[w] = v;
                que.push(w);
            }
        }
    }

    return {order, parents};
}
