#include <vector>

// 累積和を計算する．
// Output: サイズ |v|+1 のvector．i番目の要素が v[0:i] の和を表す．
template <class T>
std::vector<T> cumsum(std::vector<T>& v) {
    std::vector<T> cum(v.size() + 1);
    for (size_t i = 0; i < v.size(); ++i) {
        cum[i + 1] = cum[i] + v[i];
    }
    return cum;
}

// 2次元累積和を計算する．
// Output: サイズ (h+1, w+1) の2次元vector（ただし，(h, w) は入力サイズ）．
//         (i, j) 要素が v[0:i, 0:j] の和を表す．
template <class T>
std::vector<std::vector<T>> cumsum2d(const std::vector<std::vector<T>>& v) {
    assert(!v.empty());
    assert(!v[0].empty());

    const int h = v.size();
    const int w = v[0].size();
    std::vector<std::vector<T>> cum_v(h + 1, std::vector<T>(w + 1));

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            cum_v[i + 1][j + 1] =
                cum_v[i + 1][j] + cum_v[i][j + 1] - cum_v[i][j] + v[i][j];
        }
    }

    return cum_v;
}