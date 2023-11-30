#pragma once

#include <cassert>
#include <vector>

// b[S] = sum_{T subset S} a[T] を満たす数列Bを計算する。
// ただし、S, Tはビット列で表現された集合である。
// 入力のサイズが2冪でない場合はassertを発生させる。
template <class T>
std::vector<T> zeta_transform(const std::vector<T>& a) {
    const int n = a.size();
    assert((n & (n - 1)) == 0);  // check n == 2^k

    std::vector<T> ret(a);
    for (int i = 1; i < n; i <<= 1) {
        for (int s = 0; s < n; ++s) {
            if ((s & i) == 0) {
                ret[s | i] += ret[s];
            }
        }
    }

    return ret;
}

// a[S] = sum_{T subset S} b[T] を満たす数列bを復元する。
// ただし、S, Tはビット列で表現された集合である。
// 入力のサイズが2冪でない場合はassertを発生させる。
template <class T>
std::vector<T> mobius_transform(const std::vector<T>& a) {
    const int n = a.size();
    assert((n & (n - 1)) == 0);  // check n == 2^k

    std::vector<T> ret(a);
    for (int i = 1; i < n; i <<= 1) {
        for (int s = 0; s < n; ++s) {
            if ((s & i) == 0) {
                ret[s | i] -= ret[s];
            }
        }
    }

    return ret;
}