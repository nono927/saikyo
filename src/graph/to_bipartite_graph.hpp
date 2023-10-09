#include <vector>

#include "./search/dfs_all.hpp"
#include "./graph.hpp"

// 2部グラフの頂点に対してラベル付けを行う．
// 入力が2部グラフでない場合は空列を返す．
// 
// 各ラベルは
// * labels[u] == labels[v]
//   <=> 頂点uとvが同じ独立集合に属する
// * labels[u] / 2 == labels[v] / 2
//   <=> 頂点uとvが同じ連結成分に属する
// をみたす．
// 
// 依存先: dfs_all
std::vector<int> to_bipartite_graph(Graph& graph) {
    const int n = graph.size();
    auto [orders, parents] = dfs_all(graph, DfsType::PreOrder);
    std::vector<int> labels(n);

    int ncc = 0;
    for (auto&& v : orders) {
        auto p = parents[v];
        if (p == -1) {
            ++ncc;
            labels[v] = 2 * ncc - 2;
        } else {
            labels[v] = (labels[p] & 1) ? 2 * ncc - 2 : 2 * ncc - 1;
        }
    }

    // 2部グラフのチェック
    for (int v = 0; v < n; ++v) {
        for (auto&& w : graph.neighbors(v)) {
            if ((labels[v] + labels[w]) % 2 == 0) {
                return std::vector<int>();
            }
        }
    }

    return labels;
}