#include <algorithm>
#include <atcoder/dsu>
#include <limits>
#include <tuple>
#include <vector>

#include "../weighted_graph.hpp"

// 無向グラフの最小全域木を求め，その重みを出力する．
// 全域木が存在しない場合，無限を返す．
WeightedGraph::weight_t minimum_spanning_tree(const WeightedGraph& graph) {
    using weight_t = WeightedGraph::weight_t;
    using node_t = WeightedGraph::node_t;
    using Edge = std::tuple<weight_t, node_t, node_t>;

    std::vector<Edge> edges;
    for (node_t u = 0; u < graph.size(); ++u) {
        for (auto&& [v, c] : graph.neighbors(u)) {
            edges.emplace_back(c, u, v);
        }
    }
    std::sort(edges.begin(), edges.end());

    weight_t sum_weights = 0;
    int num_edges = 0;
    atcoder::dsu uf(graph.size());
    for (auto&& [c, u, v] : edges) {
        if (uf.same(u, v)) {
            continue;
        }
        uf.merge(u, v);
        sum_weights += c;
        ++num_edges;
        if (num_edges + 1 >= graph.size()) {
            return sum_weights;
        }
    }

    return std::numeric_limits<weight_t>::max();
}