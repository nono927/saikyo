#include "graph/graph.hpp"

Graph make_line_graph(int num_node) {
    Graph graph(num_node);
    for (int i = 0; i < num_node - 1; ++i) {
        graph.add_edge(i, i + 1);
        graph.add_edge(i + 1, i);
    }
    return graph;
}

Graph make_binary_tree(int depth) {
    int num_node = (1 << depth) - 1;
    Graph graph(num_node);
    for (int i = 1; i < num_node; ++i) {
        int p = (i + 1) / 2 - 1;
        graph.add_edge(p, i);
        graph.add_edge(i, p);
    }
    return graph;
}

Graph make_perfect_graph(int num_node) {
    Graph graph(num_node);
    for (int i = 0; i < num_node; ++i) {
        for (int j = 0; j < num_node; ++j) {
            if (i != j) {
                graph.add_edge(i, j);
            }
        }
    }
    return graph;
}