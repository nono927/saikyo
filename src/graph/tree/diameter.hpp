#include <tuple>

#include "../search/dfs.hpp"

// 木の直径を求める
// Output: (直径，端点1，端点2)
// 依存先: dfs
std::tuple<int, Graph::node_t, Graph::node_t> tree_diameter(Graph& graph) {
    using node_t = Graph::node_t;

    // sourceから最も遠い点を求める
    // Output: (最も遠い点，距離)
    auto find_farthest_node = [&](node_t source) -> std::tuple<node_t, int> {
        auto [orders, parents] = dfs(graph, source, DfsType::PreOrder);

        std::vector<int> distances(graph.size());
        distances[source] = 0;
        for (auto&& u : orders) {
            auto p = parents[u];
            if (p != -1) {
                distances[u] = distances[p] + 1;
            }
        }

        node_t farthest_node = source;
        int max_distance = 0;
        for (int u = 0; u < graph.size(); ++u) {
            if (max_distance < distances[u]) {
                farthest_node = u;
                max_distance = distances[u];
            }
        }

        return {farthest_node, max_distance};
    };

    auto [u, _] = find_farthest_node(0);
    auto [v, d] = find_farthest_node(u);
    return {d, u, v};
}
