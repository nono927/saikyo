#include <stack>
#include <tuple>

#include "../graph.hpp"

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

    std::stack<node_t> st;
    st.push(root);
    std::vector<bool> used(n);
    for (int t = 0; t < 2 * n; ++t) {
        assert(!st.empty());
        node_t v = st.top();
        st.pop();
        used[v] = true;

        if (v < n) {  // forward
            tin[v] = t;
            st.push(v + n);
            for (auto w : graph.neighbors(v)) {
                if (!used[w]) {
                    st.push(w);
                }
            }
        } else {  // backward
            v -= n;
            tout[v] = t;
        }
    }
    assert(st.empty());

    return {tin, tout};
}
