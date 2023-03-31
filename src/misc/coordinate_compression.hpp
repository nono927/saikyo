#include <algorithm>
#include <vector>

using ll = long long;

// 入力vectorを座標圧縮する．
// 圧縮後の要素がiであるとき，元の値は戻り値のi番目の要素である．
std::vector<ll> coordinate_compression(std::vector<ll>& vec) {
    std::vector<ll> decode(vec);
    std::sort(decode.begin(), decode.end());
    decode.erase(std::unique(decode.begin(), decode.end()), decode.end());
    for (size_t i = 0; i < vec.size(); ++i) {
        auto it = std::lower_bound(decode.begin(), decode.end(), vec[i]);
        vec[i] = std::distance(decode.begin(), it);
    }
    return decode;
}