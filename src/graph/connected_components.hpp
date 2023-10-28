#pragma once

#include <atcoder/dsu.hpp>
#include <utility>
#include <vector>

#include "graph.hpp"

// グラフを連結成分に分解する．
//
// 出力はタプル (ids, subgraph) の列．
// ただし，
// * ids[i]: subgraphの頂点iの，元のグラフにおけるid
// * subgraph: 連結成分
// を表す．
std::vector<std::pair<std::vector<Graph::node_t>, Graph>> connected_components(
    const Graph& graph) {
    using node_t = Graph::node_t;

    const node_t n = graph.size();
    atcoder::dsu uf(n);
    for (node_t u = 0; u < n; ++u) {
        for (auto&& v : graph.neighbors(u)) {
            uf.merge(u, v);
        }
    }

    std::vector<node_t> local_ids(n);
    std::vector<std::pair<std::vector<Graph::node_t>, Graph>> ret;
    for (auto&& group : uf.groups()) {
        const int m = group.size();
        for (int i = 0; i < m; ++i) {
            node_t u = group[i];
            local_ids[u] = i;
        }

        Graph subgraph(m);
        for (auto&& u : group) {
            node_t i = local_ids[u];
            for (auto&& v : graph.neighbors(u)) {
                node_t j = local_ids[v];
                subgraph.add_edge(i, j);
            }
        }
        ret.emplace_back(group, subgraph);
    }

    return ret;
}