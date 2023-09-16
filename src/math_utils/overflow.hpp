#pragma once

using ll = long long;

// a * b > th ならばtrueを返す．
bool is_mul_greater_than(ll a, ll b, ll th) {
    return __int128_t(a) * __int128_t(b) > th;
}