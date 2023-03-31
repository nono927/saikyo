#include <algorithm>
#include <cassert>
#include <string>
#include <type_traits>

using ll = long long;

// x >= 2^k をみたす最大のkを返す．
// x <= 0 のとき，-1を返す．
int floor_log2(ll x) {
    int ret = -1;
    while (x > 0) {
        ++ret;
        x /= 2;
    }
    return ret;
}

// x <= 2^k をみたす最小のkを返す．
int ceil_log2(ll x) {
    int ret = 1;
    while ((1 << ret) < x) {
        ++ret;
    }
    return ret;
}

// a * b > th ならばtrueを返す．
bool is_mul_more_than(ll a, ll b, ll th) {
    return __int128_t(a) * __int128_t(b) > th;
}

// 10進法における各桁の和を返す．
int digit_sum(ll x) {
    assert(x >= 0);
    int sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

// 非負整数xをn進数表記に変換する．
// ただし，nは2以上10以下とする．
std::string base_10_to_n(ll x, int n) {
    assert(n >= 2 && n <= 10);
    assert(x >= 0);
    if (x == 0) {
        return std::string("0");
    }

    std::string ret;
    while (x > 0) {
        ret += '0' + (x % n);
        x /= n;
    }
    std::reverse(ret.begin(), ret.end());
    return ret;
}

// n進数表記された非負整数xを10進数表記に直す．
// ただし，nは2以上10以下とする．
ll base_n_to_10(const std::string& x, int n) {
    assert(n >= 2 && n <= 10);
    ll ret = 0;
    ll base = 1;
    for (int i = x.size() - 1; i >= 0; --i) {
        ll digit = x[i] - '0';
        assert(digit >= 0 && digit < n);
        ret += (x[i] - '0') * base;
        base *= n;
    }
    return ret;
}