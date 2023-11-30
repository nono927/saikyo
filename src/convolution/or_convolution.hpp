#include <cassert>
#include <vector>

#include "zeta_mobius_transform.hpp"

// c[i] = sum_{i = j or k} a[j] * b[k] を満たす数列を計算する。
template <class T>
std::vector<T> or_convolution(const std::vector<T>& a,
                               const std::vector<T>& b) {
    assert(a.size() == b.size());
    auto A = zeta_transform(a);
    auto B = zeta_transform(b);

    int n = a.size();
    for (int i = 0; i < n; ++i) {
        A[i] *= B[i];
    }
    return mobius_transform(A);
}