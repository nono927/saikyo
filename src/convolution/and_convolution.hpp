#include <cassert>
#include <vector>

#include "or_convolution.hpp"

// c[i] = sum_{i = j and k} a[j] * b[k] を満たす数列を計算する。
template <class T>
std::vector<T> and_convolution(const std::vector<T>& a,
                               const std::vector<T>& b) {
    assert(a.size() == b.size());
    auto A = a;
    auto B = b;
    std::reverse(A.begin(), A.end());
    std::reverse(B.begin(), B.end());
    A = or_convolution(A, B);
    std::reverse(A.begin(), A.end());
    return A;
}