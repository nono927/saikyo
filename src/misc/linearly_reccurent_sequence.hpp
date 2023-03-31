#include <atcoder/convolution.hpp>
#include <vector>

using ll = long long;
using ModInt = atcoder::modint998244353;

// 以下で定まる数列A[n]の第n項を求める．
// - 初期条件: A[i] = inits[i] (0 <= i < d)
// - 漸化式: A[i] = coeffs[0] * A[i-1] + ... + coeffs[d-1] * A[i-d] (i >= d)
// ただし，dは初期値inits, 係数coeffsのサイズ．
ModInt nth_linearly_reccurent_sequence(ll n, std::vector<ModInt>& inits,
                                       std::vector<ModInt>& coeffs) {
    // Bostan-Mori algorithm
    assert(inits.size() == coeffs.size());
    const int d = coeffs.size();
    std::vector<ModInt> Q(d + 1);
    Q[0] = 1;
    for (int i = 0; i < d; ++i) {
        Q[i + 1] = -coeffs[i];
    }
    auto P = atcoder::convolution(inits, Q);
    P.resize(d);
    while (!P.empty() && P.back() == 0) {
        P.pop_back();
    }

    while (n > 0) {
        std::vector<ModInt> R(Q);
        for (int i = 1; i < (int)Q.size(); i += 2) {
            R[i] = -R[i];
        }
        P = atcoder::convolution(P, R);
        Q = atcoder::convolution(Q, R);

        int sz_P = 0;
        for (int i = (int)(n & 1LL); i < (int)P.size(); i += 2) {
            P[sz_P++] = P[i];
        }
        P.resize(sz_P);

        int sz_Q = 0;
        for (int i = 0; i < (int)Q.size(); i += 2) {
            Q[sz_Q++] = Q[i];
        }
        Q.resize(sz_Q);

        n >>= 1;
    }

    return P[0];
}