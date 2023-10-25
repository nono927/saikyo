#include <cassert>
#include <tuple>

using ll = long long;

// a と b の最大公約数 d を返す．
// また，a * x + b * y = c をみたす x, y を1つ求める．
//
// 戻り値: (d, x, y)
// ただし，x, y は以下の条件を満たす．
// * x >= 0
// * |x| <= b / d
// * |y| <= a / d
std::tuple<ll, ll, ll> extended_gcd(ll a, ll b) {
    assert(a > 0);
    assert(b > 0);

    if (a < b) {
        auto [d, x, y] = extended_gcd(b, a);
        if (y < 0) {
            y += b / d;
            x -= a / d;
        }
        return {d, y, x};
    }

    ll s = a, t = b;
    ll xs = 1, ys = 0;
    ll xt = 0, yt = 1;

    while (s % t != 0) {
        ll tmp = s / t;
        ll u = s - t * tmp;
        ll xu = xs - xt * tmp;
        ll yu = ys - yt * tmp;

        s = t;
        xs = xt;
        ys = yt;
        t = u;
        xt = xu;
        yt = yu;
    }

    if (xt < 0) {
        xt += b / t;
        yt -= a / t;
    }
    return {t, xt, yt};
}