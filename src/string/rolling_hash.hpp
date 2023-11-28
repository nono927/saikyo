#pragma once

#include <cassert>
#include <random>
#include <vector>

// 部分文字列に対するハッシュを計算するクラス
class RollingHash {
    using hash_t = unsigned long long;

    constexpr static hash_t MOD = (1UL << 61) - 1;
    constexpr static hash_t MASK30 = (1UL << 30) - 1;
    constexpr static hash_t MASK31 = (1UL << 31) - 1;
    static std::vector<hash_t> base_pows;

    std::vector<hash_t> prefix_hash;

    hash_t mod_hash(hash_t x) {
        hash_t xu = x >> 61;
        hash_t xd = x & MOD;
        hash_t res = xu + xd;
        if (res >= MOD) {
            res -= MOD;
        }
        return res;
    }

    hash_t mul_hash(hash_t a, hash_t b) {
        hash_t au = a >> 31;
        hash_t ad = a & MASK31;
        hash_t bu = b >> 31;
        hash_t bd = b & MASK31;
        hash_t mid = ad * bu + au * bd;
        hash_t midu = mid >> 30;
        hash_t midd = mid & MASK30;
        return mod_hash(au * bu * 2 + midu + (midd << 31) + ad * bd);
    }

    void init_base() {
        std::random_device seed_gen;
        std::mt19937_64 engine(seed_gen());
        std::uniform_int_distribution<hash_t> dist(2, MOD - 2);

        base_pows.push_back(1UL);
        base_pows.push_back(dist(engine));
    }

    void extend_base_pows(size_t n) {
        if (base_pows.empty()) {
            init_base();
        }
        if (n <= base_pows.size()) {
            return;
        }

        base_pows.reserve(n);
        hash_t b = base_pows[1];
        for (size_t i = base_pows.size(); i < n; ++i) {
            auto h = mul_hash(base_pows.back(), b);
            base_pows.push_back(h);
        }
    }

   public:
    // '\0'を含まない文字列sに対するRollingHashを生成する．
    RollingHash(const std::string s) {
        extend_base_pows(s.size());
        auto b = base_pows[1];
        prefix_hash.reserve(s.size() + 1);
        prefix_hash.push_back(0UL);
        for (auto&& x : s) {
            assert(x != '\0');
            auto h = prefix_hash.back();
            prefix_hash.push_back(
                mod_hash(mul_hash(h, b) + static_cast<hash_t>(x)));
        }
    }

    // 0を含まない数列vに対するRollingHashを生成する．
    template <class T>
    RollingHash(const std::vector<T> v) {
        extend_base_pows(v.size());
        auto b = base_pows[1];
        prefix_hash.reserve(v.size() + 1);
        prefix_hash.push_back(0UL);
        for (auto&& x : v) {
            assert(x != 0);
            auto h = prefix_hash.back();
            prefix_hash.push_back(
                mod_hash(mul_hash(h, b) + static_cast<hash_t>(x)));
        }
    }

    // 区間 [l:r] に対するハッシュを計算する
    hash_t hash(int l, int r) {
        assert(0 <= l && l <= r && r < static_cast<int>(prefix_hash.size()));
        hash_t m = mul_hash(prefix_hash[l], base_pows[r - l]);
        if (prefix_hash[r] < m) {
            return MOD + prefix_hash[r] - m;
        }
        return prefix_hash[r] - m;
    }

    // 区間 [l:r] に対するハッシュを計算する
    hash_t operator()(int l, int r) { return hash(l, r); }
};

std::vector<RollingHash::hash_t> RollingHash::base_pows;
