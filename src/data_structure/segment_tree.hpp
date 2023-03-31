#include <atcoder/all>

// ac-library のクラスである
// segtree および lazy_segtree のための設定集

using namespace std;
using namespace atcoder;
using ll = long long;
constexpr ll LL_INFTY = 1e18;

// segtree
// 区間の総和を取得
namespace segtree_sum {

using data_t = int;
data_t bin_op(data_t a, data_t b) { return a + b; }
data_t unit() { return 0; }
using SegTree = segtree<data_t, bin_op, unit>;

}  // namespace segtree_sum

// segtree
// 区間の最大値を取得
namespace segtree_max {

using data_t = ll;
data_t bin_op(data_t a, data_t b) { return max(a, b); }
data_t unit() { return -LL_INFTY; }
using SegTree = segtree<data_t, bin_op, unit>;

}  // namespace segtree_max

// lazy_segtree
// 区間の最大値を取得
// 区間に対してmaxを適用
namespace lazy_segtree_max_max {

struct Monoid {
    using data_t = ll;

    data_t x;

    Monoid(const data_t x) : x(x) {}

    Monoid operator*=(const Monoid& rhs) {
        x = max(x, rhs.x);
        return *this;
    }

    static Monoid unit() { return Monoid(-LL_INFTY); }

    data_t val() const { return x; }
};

struct Mapping {
    using data_t = Monoid::data_t;

    data_t x;

    Mapping(const data_t x) : x(x) {}

    Monoid operator()(const Monoid& m) const { return Monoid(max(m.x, x)); }

    Mapping operator*=(const Mapping& rhs) {
        x = max(x, rhs.x);
        return *this;
    }

    static Mapping id() { return Mapping(Monoid::unit().val()); }
};

Monoid _op(Monoid lhs, Monoid rhs) { return Monoid(lhs) *= rhs; }
Monoid _mapping(Mapping f, Monoid x) { return f(x); }
Mapping _composition(Mapping f, Mapping g) { return Mapping(f) *= g; }
using LazySegTree = lazy_segtree<Monoid, _op, Monoid::unit, Mapping, _mapping,
                                 _composition, Mapping::id>;

}  // namespace lazy_segtree_max_max

// lazy_segtree
// 区間の総和を取得
// 区間に対してアフィン変換を適用
namespace lazy_segtree_sum_affine {

struct Monoid {
    using data_t = ll;

    data_t value, length;

    Monoid(const data_t v, data_t l) : value(v), length(l) {}

    Monoid operator*=(const Monoid& rhs) {
        value += rhs.value;
        length += rhs.length;
        return *this;
    }

    static Monoid unit() { return Monoid(0, 0); }

    data_t val() const { return value; }
};

struct Mapping {
    using data_t = Monoid::data_t;

    data_t a, b;

    Mapping(const data_t b, const data_t c) : a(b), b(c) {}

    Monoid operator()(const Monoid& m) const {
        return Monoid(a * m.value + b * m.length, m.length);
    }

    Mapping operator*=(const Mapping& rhs) {
        b += a * rhs.b;
        a *= rhs.a;
        return *this;
    }

    static Mapping id() { return Mapping(1, 0); }
};

Monoid _op(Monoid lhs, Monoid rhs) { return Monoid(lhs) *= rhs; }
Monoid _mapping(Mapping f, Monoid x) { return f(x); }
Mapping _composition(Mapping f, Mapping g) { return Mapping(f) *= g; }
using LazySegTree = lazy_segtree<Monoid, _op, Monoid::unit, Mapping, _mapping,
                                 _composition, Mapping::id>;

}  // namespace lazy_segtree_sum_affine
