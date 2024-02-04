#pragma once

#include <cassert>
#include <vector>

using ll = long long;

template <class T = ll>
struct Doubling {
    // nexts: 整数 0, ..., nexts.size() を定義域とする関数のvector表現．
    // max_nsteps:
    // 正しい動作が保証されるステップ数の上限．これを超えた場合の動作は未定義．
    Doubling(std::vector<T>& nexts, ll max_nsteps) {
        assert(max_nsteps > 0);
        LOG_MAX_STEPS = floor_log2(max_nsteps) + 1;
        _nexts.resize(LOG_MAX_STEPS);
        _nexts[0] = nexts;

        for (int k = 1; k < LOG_MAX_STEPS; ++k) {
            _nexts[k].resize(nexts.size());
            for (int i = 0; i < (int)nexts.size(); ++i) {
                T nxt = _nexts[k - 1][i];
                if (check_range(nxt)) {
                    _nexts[k][i] = _nexts[k - 1][nxt];
                } else {
                    _nexts[k][i] = -1;
                }
            }
        }
    }

    // xに関数nextsをnstep回適用した後の値を求める．
    T step(T x, ll nsteps) {
        assert(nsteps >= 0);
        T ret = x;
        for (int k = LOG_MAX_STEPS - 1; k >= 0; --k) {
            if (!check_range(ret)) {
                return -1;
            }
            ll pow2 = 1LL << k;
            if (nsteps & pow2) {
                ret = _nexts[k][ret];
                nsteps -= pow2;
            }
        }
        return ret;
    }

   private:
    int LOG_MAX_STEPS;
    std::vector<std::vector<T>> _nexts;

    bool check_range(T i) { return i >= 0 && i < (T)_nexts[0].size(); }

    int floor_log2(ll x) {
        int ret = -1;
        while (x > 0) {
            ++ret;
            x /= 2;
        }
        return ret;
    }
};