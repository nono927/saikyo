// !! 古いバージョン !!
// いくつかのライブラリが本バージョンに依存していそうなので，残しておく．
// 依存が無くなったことを確認できたタイミングで消す．

#pragma once

#include <queue>
#include <tuple>
#include <vector>

#include "./graph.hpp"

// グラフに対してBFSを行い，タプル
// (到達した頂点の集合, BFS木における各ノードの親)
// を返す．
//
// 到達した頂点は，早く訪れた順にソートされている．
// 探索の始点，または到達していない頂点の親は-1とする．
std::tuple<std::vector<Graph::node_t>, std::vector<Graph::node_t>> bfs(
    const Graph& graph, const Graph::node_t source) {
    using node_t = Graph::node_t;

    const int n = graph.size();
    std::vector<node_t> order;
    std::vector<node_t> parents(n, -1);
    order.reserve(n);

    {
        std::queue<node_t> que;
        std::vector<bool> used(n);
        que.push(source);
        used[source] = true;
        while (!que.empty()) {
            node_t v = que.front();
            que.pop();
            order.push_back(v);
            for (auto w : graph.neighbors(v)) {
                if (!used[w]) {
                    used[w] = true;
                    parents[w] = v;
                    que.push(w);
                }
            }
        }
    }

    return {order, parents};
}
