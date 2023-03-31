#pragma once

#include <cassert>
#include <utility>
#include <vector>

struct WeightedGraph {
    using node_t = int;
    using weight_t = long long;
    using edge_t = std::pair<node_t, weight_t>;

    std::vector<std::vector<edge_t> > _neighbors;

    WeightedGraph(int n) : _neighbors(std::vector<std::vector<edge_t> >(n)) {}

    void check_id_range(node_t v) {
        assert(v >= 0 && v < static_cast<node_t>(_neighbors.size()));
    }

    void add_edge(node_t u, node_t v, weight_t c) {
        check_id_range(v);
        _neighbors[u].emplace_back(v, c);
    }

    int size() const { return static_cast<int>(_neighbors.size()); }

    const std::vector<edge_t>& neighbors(node_t v) const {
        return _neighbors[v];
    }
};

WeightedGraph make_directed_wgraph(int num_nodes,
                                   std::vector<WeightedGraph::node_t>& xs,
                                   std::vector<WeightedGraph::node_t>& ys,
                                   std::vector<WeightedGraph::weight_t>& ws,
                                   int indexed_by = 1) {
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

WeightedGraph make_undirected_wgraph(int num_nodes,
                                     std::vector<WeightedGraph::node_t>& xs,
                                     std::vector<WeightedGraph::node_t>& ys,
                                     std::vector<WeightedGraph::weight_t>& ws,
                                     int indexed_by = 1) {
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
