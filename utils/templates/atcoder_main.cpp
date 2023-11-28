#include <bits/stdc++.h>

#include <atcoder/all>

using namespace std;
using namespace atcoder;

using ll = long long;
using VecBool = vector<bool>;
using VecInt = vector<int>;
using VecLL = vector<ll>;

constexpr int INFTY = 1e9;
constexpr ll LL_INFTY = 1e18;

#define REP(i, n) for (ll i = 0; i < ll(n); ++i)
#define REP3(i, m, n) for (ll i = (m); i < ll(n); ++i)
#define REPR(i, n) for (ll i = ll(n) - 1; i >= 0; --i)
#define REP3R(i, m, n) for (ll i = ll(n) - 1; i >= ll(m); --i)

#define ALL(x) (x).begin(), (x).end()
#define EACH(e, x) for (auto&& e : x)
#define EACHP(e1, e2, x) for (auto&& [e1, e2] : x)

template <class T, size_t N>
auto make_ndvector(const ll (&dims)[N], T init) {
    if constexpr (N == 1) {
        return std::vector(dims[0], init);
    } else {
        ll next_dims[N - 1] = {};
        for (size_t i = 0; i < N - 1; ++i) {
            next_dims[i] = dims[i + 1];
        }
        return std::vector(dims[0], make_ndvector<T, N - 1>(next_dims, init));
    }
}

template <class T, size_t N>
auto make_ndvector(const ll (&dims)[N]) {
    return make_ndvector(dims, T());
}

#ifdef LOCAL
#include "local_debug.hpp"
#else
#define ASSERT(x) 0
#define DUMP(x) 0
#endif

using ModInt = modint998244353;
using VecModInt = vector<ModInt>;

int main() {}