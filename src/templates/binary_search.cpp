#include <cassert>
#include <cstdlib>

using namespace std;
using ll = long long;

// 条件 cond(x) を満たすxの境界値を求める．
template <class T>
ll bin_search(ll ok, ll ng, T cond) {
    assert(cond(ok));
    assert(!cond(ng));
    while (abs(ng - ok) > 1) {
        ll mid = (ok + ng) / 2;
        if (cond(mid)) {
            ok = mid;
        } else {
            ng = mid;
        }
    }
    return ok;
}