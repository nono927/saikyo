#pragma once

#include <cassert>
#include <vector>

struct Graph {
    using node_t = int;

    std::vector<std::vector<node_t> > _neighbors;

    Graph(int n) : _neighbors(std::vector<std::vector<node_t> >(n)) {}

    void check_id_range(node_t v) {
        assert(v >= 0 && v < static_cast<node_t>(_neighbors.size()));
    }

    void add_edge(node_t u, node_t v) {
        check_id_range(v);
        _neighbors[u].push_back(v);
    }

    int size() const { return static_cast<int>(_neighbors.size()); }

    const std::vector<node_t>& neighbors(node_t v) const {
        return _neighbors[v];
    }
};

Graph make_directed_graph(int num_nodes, std::vector<Graph::node_t>& xs,
                          std::vector<Graph::node_t>& ys, int indexed_by = 1) {
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

Graph make_undirected_graph(int num_nodes, std::vector<Graph::node_t>& xs,
                            std::vector<Graph::node_t>& ys,
                            int indexed_by = 1) {
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
