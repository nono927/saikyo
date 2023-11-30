#pragma once

#include <cassert>
#include <vector>

template <class T>
std::vector<T> fast_walsh_hadamard_transform(const std::vector<T>& a) {
    const int n = a.size();
    assert(n > 0);
    assert((n & (n - 1)) == 0);  // check n == 2^k

    std::vector<T> ret(a);
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; ++j) {
            if ((i & j) == 0) {
                T x = ret[j];
                T y = ret[i + j];
                ret[j] = x + y;
                ret[i + j] = x - y;
            }
        }
    }

    return ret;
}

template <class T>
std::vector<T> inverse_fast_walsh_hadamard_transform(const std::vector<T>& a) {
    auto ret = fast_walsh_hadamard_transform(a);
    T m = ret.size();
    for (auto&& x : ret) {
        x /= m;
    }
    return ret;
}

// c[i] = sum_{i = j xor k} a[j] * b[k] を満たす数列を計算する。
template <class T>
std::vector<T> xor_convolution(const std::vector<T>& a,
                               const std::vector<T>& b) {
    assert(a.size() == b.size());
    auto A = fast_walsh_hadamard_transform(a);
    auto B = fast_walsh_hadamard_transform(b);

    int n = a.size();
    for (int i = 0; i < n; ++i) {
        A[i] *= B[i];
    }
    return inverse_fast_walsh_hadamard_transform(A);
}