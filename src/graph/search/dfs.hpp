#pragma once

#include <stack>
#include <tuple>
#include <vector>

#include "../graph.hpp"

// DFSが出力する頂点の順番のタイプ
enum class DfsType {
    // 頂点を初めて訪れたタイミング順に返す．
    PreOrder,
    // 頂点を最後に訪れたタイミング順に返す．
    PostOrder,
    // 頂点 v を初めて訪れたタイミングで v，
    // 最後に訪れたタイミングで v + n を返す．
    // (n はグラフに含まれる頂点の数)
    Euler,
};

// グラフに対してDFSを行い，タプル
// (探索した頂点の順番, DFS木における各ノードの親)
// を返す．
//
// 同じ頂点から複数の辺が出ている場合は，先に追加した辺から順に探索する．
// 頂点 v が探索の始点，または到達しなかった頂点の時，v の親は -1 とする．
std::tuple<std::vector<Graph::node_t>, std::vector<Graph::node_t>> dfs(
    const Graph& graph, const Graph::node_t source,
    const DfsType dfs_type = DfsType::PostOrder) {
    using node_t = Graph::node_t;

    const int n = graph.size();
    std::vector<node_t> order;
    std::vector<node_t> parents(n, -1);

    std::stack<node_t> st;
    std::vector<bool> used(n);
    st.push(source);
    while (!st.empty()) {
        node_t v = st.top();
        st.pop();

        if (v >= n) {  // post-order
            order.push_back(v);
            continue;
        }

        if (used[v]) {
            continue;
        }
        used[v] = true;

        if (dfs_type != DfsType::PostOrder) {
            order.push_back(v);
        }
        if (dfs_type != DfsType::PreOrder) {
            st.push(v + n);
        }

        auto& neighbors = graph.neighbors(v);
        for (int i = neighbors.size() - 1; i >= 0; --i) {
            node_t w = neighbors[i];
            if (!used[w]) {
                parents[w] = v;
                st.push(w);
            }
        }
    }

    if (dfs_type == DfsType::PostOrder) {
        for (auto&& v : order) {
            v -= n;
        }
    }

    return {order, parents};
}