#pragma once

#include <string>

using ll = long long;

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