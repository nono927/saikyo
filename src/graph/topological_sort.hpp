#pragma once

#include <queue>
#include <vector>

#include "./graph.hpp"

// 入力グラフのトポロジカルソートを返す．
// 入力にサイクルが存在する場合．空のvectorを返す．
std::vector<Graph::node_t> topological_sort(const Graph& graph) {
    using node_t = Graph::node_t;
    const int n = graph.size();

    std::vector<int> deg_in(n);
    for (int v = 0; v < n; ++v) {
        for (auto w : graph.neighbors(v)) {
            ++deg_in[w];
        }
    }

    std::vector<node_t> orders;
    orders.reserve(n);
    {
        std::queue<node_t> que;
        for (int v = 0; v < n; ++v) {
            if (deg_in[v] == 0) {
                que.push(v);
            }
        }
        while (!que.empty()) {
            auto v = que.front();
            que.pop();
            orders.push_back(v);
            for (auto w : graph.neighbors(v)) {
                --deg_in[w];
                if (deg_in[w] == 0) {
                    que.push(w);
                }
            }
        }
    }

    if (static_cast<int>(orders.size()) < n) {  // cycle exists
        return std::vector<node_t>();
    }

    return orders;
}
