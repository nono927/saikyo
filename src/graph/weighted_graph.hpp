#pragma once

#include <cassert>
#include <utility>
#include <vector>

// 重みつきグラフを表すクラス
struct WeightedGraph {
    using node_t = int;
    using weight_t = long long;
    using edge_t = std::pair<node_t, weight_t>;

    std::vector<std::vector<edge_t> > _neighbors;

    // 頂点数nの、辺を持たないグラフを生成する。
    WeightedGraph(int n) : _neighbors(std::vector<std::vector<edge_t> >(n)) {}

    // コストcの有向辺 (u, v) を追加する。
    void add_edge(node_t u, node_t v, weight_t c) {
        check_id_range(v);
        _neighbors[u].emplace_back(v, c);
    }

    // 頂点数を返す。
    int size() const { return static_cast<int>(_neighbors.size()); }

    // 頂点vの出次数を返す。
    int deg(node_t v) const {
        check_id_range(v);
        return static_cast<int>(_neighbors[v].size());
    }

    // 頂点vから出る辺の集合を、(行き先の頂点, コスト) のタプル列として返す。
    const std::vector<edge_t>& neighbors(node_t v) const {
        return _neighbors[v];
    }

   private:
    void check_id_range(node_t v) const {
        assert(v >= 0 && v < static_cast<node_t>(_neighbors.size()));
    }
};

// 頂点数n、重み ws[i] の有向辺 (xs[i], ys[i]) を持つグラフを生成する。
WeightedGraph make_directed_wgraph(
    const int num_nodes, const std::vector<WeightedGraph::node_t>& xs,
    const std::vector<WeightedGraph::node_t>& ys,
    const std::vector<WeightedGraph::weight_t>& ws, const int indexed_by = 1) {
    assert(xs.size() == ys.size());
    assert(indexed_by >= 0);

    using node_t = WeightedGraph::node_t;

    WeightedGraph graph(num_nodes);
    const int n = xs.size();
    for (int i = 0; i < n; ++i) {
        node_t x = xs[i] - indexed_by;
        node_t y = ys[i] - indexed_by;
        graph.add_edge(x, y, ws[i]);
    }
    return graph;
}

// 頂点数n、重み ws[i] の無向辺 (xs[i], ys[i]) を持つグラフを生成する。
WeightedGraph make_undirected_wgraph(
    const int num_nodes, const std::vector<WeightedGraph::node_t>& xs,
    const std::vector<WeightedGraph::node_t>& ys,
    const std::vector<WeightedGraph::weight_t>& ws, const int indexed_by = 1) {
    assert(xs.size() == ys.size());
    assert(indexed_by >= 0);

    using node_t = WeightedGraph::node_t;

    WeightedGraph graph(num_nodes);
    const int n = xs.size();
    for (int i = 0; i < n; ++i) {
        node_t x = xs[i] - indexed_by;
        node_t y = ys[i] - indexed_by;
        graph.add_edge(x, y, ws[i]);
        graph.add_edge(y, x, ws[i]);
    }
    return graph;
}
