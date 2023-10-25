#include <cassert>
#include <utility>
#include <vector>

using ll = long long;

// 正の整数nを素因数分解し，（素数，指数）の列を出力する．
// 出力は，素数に関して昇順にソートされている．
// n = 1 のときは空列を返す．
std::vector<std::pair<ll, int>> prime_factorization(ll n) {
    assert(n > 0);
    std::vector<std::pair<ll, int>> ret;
    for (ll p = 2; p * p <= n; ++p) {
        if (n % p != 0) {
            continue;
        }
        int exponent = 0;
        while (n % p == 0) {
            ++exponent;
            n /= p;
        }
        ret.emplace_back(p, exponent);
    }
    if (n > 1) {
        ret.emplace_back(n, 1);
    }
    return ret;
}