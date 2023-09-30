// !! 古いバージョン !!
// いくつかのライブラリが本バージョンに依存していそうなので，残しておく．
// 依存が無くなったことを確認できたタイミングで消す．

#pragma once

#include <stack>
#include <tuple>
#include <vector>

#include "./graph.hpp"

// グラフに対してDFSを行い，タプル
// (到達した頂点の集合, DFS木における各ノードの親)
// を返す．
//
// 到達した頂点は，早く訪れた順にソートされている．
// 探索の始点，または到達していない頂点の親は-1とする．
std::tuple<std::vector<Graph::node_t>, std::vector<Graph::node_t>> dfs(
    const Graph& graph, const Graph::node_t source) {
    using node_t = Graph::node_t;

    const int n = graph.size();
    std::vector<node_t> order;
    std::vector<node_t> parents(n, -1);
    order.reserve(n);

    {
        std::stack<node_t> st;
        std::vector<bool> used(n);
        st.push(source);
        while (!st.empty()) {
            node_t v = st.top();
            st.pop();
            if (used[v]) {
                continue;
            }
            used[v] = true;
            order.push_back(v);
            for (auto w : graph.neighbors(v)) {
                if (!used[w]) {
                    parents[w] = v;
                    st.push(w);
                }
            }
        }
    }

    return {order, parents};
}

// グラフに対してDFSを行い，タプル
// (到達した頂点の集合, DFS木における各ノードの親)
// を返す．
//
// 到達した頂点は，早く訪れた順にソートされている．
// 探索の始点の親は-1とする．
std::tuple<std::vector<Graph::node_t>, std::vector<Graph::node_t>> dfs_all(
    const Graph& graph) {
    using node_t = Graph::node_t;

    const int n = graph.size();
    std::vector<node_t> order;
    std::vector<node_t> parents(n, -1);
    order.reserve(n);

    std::stack<node_t> st;
    std::vector<bool> used(n);
    for (node_t u = 0; u < n; ++u) {
        if (used[u]) {
            continue;
        }
        st.push(u);
        while (!st.empty()) {
            node_t v = st.top();
            st.pop();
            if (used[v]) {
                continue;
            }
            used[v] = true;
            order.push_back(v);
            for (auto w : graph.neighbors(v)) {
                if (!used[w]) {
                    parents[w] = v;
                    st.push(w);
                }
            }
        }
    }

    return {order, parents};
}
