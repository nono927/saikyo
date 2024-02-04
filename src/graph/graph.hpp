#pragma once

#include <cassert>
#include <vector>

// 重みなしグラフを表すクラス
struct Graph {
    using node_t = int;

    std::vector<std::vector<node_t> > _neighbors;

    // 頂点数nの、辺を持たないグラフを生成する。
    Graph(int n) : _neighbors(std::vector<std::vector<node_t> >(n)) {}

    // 有向辺 (u, v) を追加する。
    void add_edge(node_t u, node_t v) {
        check_id_range(v);
        _neighbors[u].push_back(v);
    }

    // 頂点数を返す。
    int size() const { return static_cast<int>(_neighbors.size()); }

    // 頂点vの出次数を返す。
    int deg(node_t v) const {
        check_id_range(v);
        return static_cast<int>(_neighbors[v].size());
    }

    // 頂点vに隣接する頂点の列を返す。
    const std::vector<node_t>& neighbors(node_t v) const {
        return _neighbors[v];
    }

   private:
    void check_id_range(node_t v) const {
        assert(v >= 0 && v < static_cast<node_t>(_neighbors.size()));
    }
};

// 頂点数n、有向辺 (xs[i], ys[i]) を持つグラフを生成する。
Graph make_directed_graph(const int num_nodes,
                          const std::vector<Graph::node_t>& xs,
                          const std::vector<Graph::node_t>& ys,
                          const int indexed_by = 1) {
    assert(xs.size() == ys.size());
    assert(indexed_by >= 0);

    using node_t = Graph::node_t;

    Graph graph(num_nodes);
    const int n = xs.size();
    for (int i = 0; i < n; ++i) {
        node_t x = xs[i] - indexed_by;
        node_t y = ys[i] - indexed_by;
        assert(x != y);
        graph.add_edge(x, y);
    }
    return graph;
}

// 頂点数n、無向辺 (xs[i], ys[i]) を持つグラフを生成する。
Graph make_undirected_graph(const int num_nodes,
                            const std::vector<Graph::node_t>& xs,
                            const std::vector<Graph::node_t>& ys,
                            const int indexed_by = 1) {
    assert(xs.size() == ys.size());
    assert(indexed_by >= 0);

    using node_t = Graph::node_t;

    Graph graph(num_nodes);
    const int n = xs.size();
    for (int i = 0; i < n; ++i) {
        node_t x = xs[i] - indexed_by;
        node_t y = ys[i] - indexed_by;
        assert(x != y);
        graph.add_edge(x, y);
        graph.add_edge(y, x);
    }
    return graph;
}
