#include <stack>
#include <tuple>

#include "../search/dfs.hpp"

// 無向木に対して，rootを始点とするeuler tourを求める．
//
// 出力 (tin, tout) はそれぞれ
// tin[i]: 頂点iに根の側から入った時刻
// tout[i]: 頂点iから根の方向に出た時刻
// を表す．
//
// ただし，tin[root] = 0, tout[root] = 2 * n - 1 (nは頂点数) である．
std::tuple<std::vector<int>, std::vector<int>> euler_tour(
    const Graph& graph, const Graph::node_t root) {
    using node_t = Graph::node_t;

    const int n = graph.size();
    std::vector<node_t> tin(n);
    std::vector<node_t> tout(n);

    auto [order, parents] = dfs(graph, root, DfsType::Euler);
    assert(order.size() == 2 * n);

    for (int i = 0; i < 2 * n; ++i) {
        node_t v = order[i];
        if (v < n) {
            tin[v] = i;
        } else {
            tout[v - n] = i;
        }
    }

    return {tin, tout};
}
