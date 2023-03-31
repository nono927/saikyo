#include <vector>

using ll = long long;

// nの約数を昇順にソートして返す．
std::vector<ll> enumerate_divisors(ll n) {
    std::vector<ll> divs_small, divs_large;
    for (ll d = 1; d * d <= n; ++d) {
        if (n % d != 0) {
            continue;
        }
        divs_small.push_back(d);
        if (d * d < n) {
            divs_large.push_back(n / d);
        }
    }
    while (!divs_large.empty()) {
        divs_small.push_back(divs_large.back());
        divs_large.pop_back();
    }
    return divs_small;
}