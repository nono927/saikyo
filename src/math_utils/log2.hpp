#pragma once

#include <cassert>

using ll = long long;

// 正の整数xに対して，x >= 2^k をみたす最大のkを返す．
int floor_log2(ll x) {
    assert(x > 0);
    int ret = -1;
    while (x > 0) {
        ++ret;
        x /= 2;
    }
    return ret;
}

// 正の整数xに対して，x <= 2^k をみたす最小のkを返す．
int ceil_log2(ll x) {
    assert(x > 0);
    int ret = 0;
    while ((1LL << ret) < x) {
        ++ret;
    }
    return ret;
}