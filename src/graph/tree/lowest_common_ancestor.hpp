#include <utility>
#include <vector>

#include "../dfs.hpp"

class LowestCommonAncestor {
    using node_t = Graph::node_t;

    int ceil_log2_nnode;
    std::vector<std::vector<node_t>> _parents;
    std::vector<int> depth;

   public:
    // 無向木に対して，最小共通祖先を求めるデータ構造を作成する．
    // 入力グラフが無向木であることはチェックされない．
    LowestCommonAncestor(Graph& graph, Graph::node_t root) {
        const int nnode = graph.size();
        ceil_log2_nnode = 1;
        while ((1 << ceil_log2_nnode) < nnode) {
            ++ceil_log2_nnode;
        }
        _parents = std::vector<std::vector<node_t>>(ceil_log2_nnode,
                                                    std::vector<node_t>(nnode));

        // init parents
        auto [order, parents] = dfs(graph, root);
        _parents[0] = parents;
        for (auto&& v : order) {
            for (int i = 0; i < ceil_log2_nnode - 1; ++i) {
                auto p = _parents[i][v];
                if (p >= 0) {
                    _parents[i + 1][v] = _parents[i][p];
                } else {
                    _parents[i + 1][v] = -1;
                }
            }
        }

        // init depth
        depth.resize(nnode);
        for (auto&& v : order) {
            auto p = parents[v];
            if (p >= 0) {
                depth[v] = depth[p] + 1;
            }
        }
    }

    // 頂点vのk個先の祖先を返す
    node_t parent(node_t v, int k) {
        if (k >= (1 << ceil_log2_nnode)) {
            return -1;
        }

        for (int i = 0; i < ceil_log2_nnode; ++i) {
            if (k & 1) {
                v = _parents[i][v];
            }
            k >>= 1;
            if (k == 0) {
                break;
            }
        }
        return v;
    }

    // 頂点u,vの最小共通祖先を返す
    node_t lca(node_t u, node_t v) {
        if (depth[u] > depth[v]) {
            std::swap(u, v);
        }
        v = parent(v, depth[v] - depth[u]);
        if (u == v) {
            return u;
        }

        for (int i = ceil_log2_nnode - 1; i >= 0; --i) {
            if (_parents[i][u] != _parents[i][v]) {
                u = _parents[i][u];
                v = _parents[i][v];
            }
        }
        return _parents[0][u];
    }

    // 頂点u,v間の距離を返す
    int distance(node_t u, node_t v) {
        return depth[u] + depth[v] - 2 * depth[lca(u, v)];
    }

    // 頂点aがu-vパス上にあればtrueを返す
    bool is_on_path(node_t a, node_t u, node_t v) {
        return distance(u, a) + distance(a, v) == distance(u, v);
    }
};
