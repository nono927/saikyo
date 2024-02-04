#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

using ll = long long;

// 座標圧縮クラス
class CoordinateCompression {
   public:
    CoordinateCompression(std::vector<ll> vec)
        : _decode(_unique(std::move(vec))) {}

    ll encode(ll x) {
        auto it = std::lower_bound(_decode.begin(), _decode.end(), x);
        assert(it != _decode.end());
        assert(*it == x);
        return it - _decode.begin();
    }

    std::vector<ll> encode(const std::vector<ll>& vec) {
        std::vector<ll> ret;
        ret.reserve(vec.size());
        for (auto&& x : vec) {
            ret.emplace_back(encode(x));
        }
        return ret;
    }

    ll decode(ll x) {
        assert(x >= 0 && x < (size_t)_decode.size());
        return _decode[x];
    }

    std::vector<ll> decode(const std::vector<ll>& vec) {
        std::vector<ll> ret;
        ret.reserve(vec.size());
        for (auto&& x : vec) {
            ret.emplace_back(decode(x));
        }
        return ret;
    }

    // decode(i) <= x < decode(i + 1) をみたすiを求める．
    // ただし，ここでは decode(-1) = -inf, decode(size) = +inf と考える．
    ll bound(ll x) {
        auto it = std::upper_bound(_decode.begin(), _decode.end(), x);
        return it - _decode.begin() - 1;
    }

    int size() { return _decode.size(); }

   private:
    const std::vector<ll> _decode;

    static std::vector<ll> _unique(std::vector<ll> vec) {
        assert(!vec.empty());
        std::sort(vec.begin(), vec.end());
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        return vec;
    }
};