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

template <class T>
std::vector<T> make_ndvector(T init, int n) {
    return std::vector<T>(n, init);
}

template <class T, class... Args>
auto make_ndvector(T init, int n, Args... args) {
    return std::vector<decltype(make_ndvector<T>(init, args...))>(
        n, make_ndvector<T>(init, args...));
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