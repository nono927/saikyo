#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

class BinaryTrie {
   public:
    using value_t = int64_t;
    using id_t = int32_t;
    static constexpr value_t EMPTY_VALUE = -1;

    BinaryTrie() { add_empty_node(); }

    // 集合に含まれる要素の数を返す。
    int size() const { return get_count(ROOT_NODE); }

    // 集合にxを追加する。
    void insert(value_t x) {
        assert(x >= 0);
        x ^= xor_val;
        id_t cur = ROOT_NODE;
        for (int height = NUM_BITS - LOG_NUM_CHILDREN; height >= 0;
             height -= LOG_NUM_CHILDREN) {
            incl_count(cur);
            cur = get_or_create_child_id(cur, value2id(x, height));
        }
        incl_count(cur);
    }

    // 集合にxが含まれていればtrue、そうでなければfalseを返す。
    bool contains(value_t x) const { return count(x) > 0; }

    // 集合にxがいくつ含まれているかを返す。
    id_t count(value_t x) const {
        assert(x >= 0);
        x ^= xor_val;
        id_t cur = ROOT_NODE;
        for (int height = NUM_BITS - LOG_NUM_CHILDREN; height >= 0;
             height -= LOG_NUM_CHILDREN) {
            cur = get_child_id(cur, value2id(x, height));
            if (cur == EMPTY_NODE) return 0;
        }
        return get_count(cur);
    }

    // 集合からxを1つ削除する。
    // 集合にxが含まれていない場合はassertが発生する。
    void erase(value_t x) {
        assert(x >= 0);
        x ^= xor_val;
        id_t cur = ROOT_NODE;
        for (int height = NUM_BITS - LOG_NUM_CHILDREN; height >= 0;
             height -= LOG_NUM_CHILDREN) {
            assert(get_count(cur) > 0);
            decl_count(cur);
            cur = get_child_id(cur, value2id(x, height));
            assert(cur != EMPTY_NODE);
        }
        assert(get_count(cur) > 0);
        decl_count(cur);
    }

    // 集合に含まれる値vのうち、v >= xを満たす最小のものを返す。
    // 存在しなければ EMPTY_VALUE を返す。
    value_t lower_bound(value_t x) const {
        assert(size() > 0);
        id_t left = -1;
        id_t right = size() - 1;
        if (kth_element(right) < x) return EMPTY_VALUE;
        while (right - left > 1) {
            id_t mid = (left + right) / 2;
            value_t val = kth_element(mid);
            if (val >= x) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return kth_element(right);
    }

    // 集合に含まれる値vのうち、v > xを満たす最小のものを返す。
    // 存在しなければ EMPTY_VALUE を返す。
    value_t upper_bound(value_t x) const { return lower_bound(x + 1); }

    // 集合に含まれる値の最大値を返す。
    value_t max_element() const {
        assert(size() > 0);
        id_t cur = ROOT_NODE;
        value_t ret = 0;
        for (int height = NUM_BITS - LOG_NUM_CHILDREN; height >= 0;
             height -= LOG_NUM_CHILDREN) {
            auto [idx, val] = get_max_child_index(cur, height);
            ret += id2value(val, height);
            cur = get_child_id(cur, idx);
        }
        return ret;
    }

    // 集合に含まれる値の最小値を返す。
    value_t min_element() const {
        assert(size() > 0);
        id_t cur = ROOT_NODE;
        value_t ret = 0;
        for (int height = NUM_BITS - LOG_NUM_CHILDREN; height >= 0;
             height -= LOG_NUM_CHILDREN) {
            auto [idx, val] = get_min_child_index(cur, height);
            ret += id2value(val, height);
            cur = get_child_id(cur, idx);
        }
        return ret;
    }

    // 集合に含まれる要素のうち、0から数えてk番目に小さいものを返す。
    value_t kth_element(int k) const {
        assert(k >= 0 && k < size());
        id_t cur = ROOT_NODE;
        value_t ret = 0;
        for (int height = NUM_BITS - LOG_NUM_CHILDREN; height >= 0;
             height -= LOG_NUM_CHILDREN) {
            auto [idx, val] = get_lower_bound_index(cur, height, k);
            ret += id2value(val, height);
            cur = get_child_id(cur, idx);
        }
        return ret;
    }

    // 集合の各要素に対して、xとのxorをとる。
    void xor_all(value_t x) { xor_val ^= x; }

   private:
    static constexpr int NUM_BITS = 63;
    static constexpr id_t ROOT_NODE = 0;
    static constexpr id_t EMPTY_NODE = -1;
    static constexpr id_t LOG_NUM_CHILDREN = 3;
    static constexpr id_t NUM_CHILDREN = 1 << (LOG_NUM_CHILDREN);

    struct Node {
        value_t cnt;
        std::array<value_t, NUM_CHILDREN> children;
        Node() : cnt(0) {
            std::fill(children.begin(), children.end(), EMPTY_NODE);
        }
    };

    std::vector<Node> nodes;
    value_t xor_val = 0;

    id_t get_child_id(id_t cur, id_t idx) const {
        return nodes[cur].children[idx];
    }

    id_t get_or_create_child_id(id_t cur, id_t idx) {
        if (id_t id = get_child_id(cur, idx); id != EMPTY_NODE) {
            return id;
        }
        id_t id = add_empty_node();
        nodes[cur].children[idx] = id;
        return id;
    }

    id_t get_count(id_t cur) const { return nodes[cur].cnt; }
    void incl_count(id_t cur) { ++nodes[cur].cnt; }
    void decl_count(id_t cur) { --nodes[cur].cnt; }

    std::pair<id_t, id_t> get_max_child_index(id_t cur, id_t height) const {
        for (id_t v = NUM_CHILDREN - 1; v >= 0; --v) {
            id_t i = v ^ value2id(xor_val, height);
            id_t child_id = get_child_id(cur, i);
            if (child_id == EMPTY_NODE) continue;
            if (get_count(child_id) > 0) return {i, v};
        }
        assert(false);
    }

    std::pair<id_t, id_t> get_min_child_index(id_t cur, id_t height) const {
        for (id_t v = 0; v < NUM_CHILDREN; ++v) {
            id_t i = v ^ value2id(xor_val, height);
            id_t child_id = get_child_id(cur, i);
            if (child_id == EMPTY_NODE) continue;
            if (get_count(child_id) > 0) return {i, v};
        }
        assert(false);
    }

    std::pair<id_t, id_t> get_lower_bound_index(id_t cur, id_t height,
                                                id_t& cnt) const {
        for (id_t v = 0; v < NUM_CHILDREN; ++v) {
            id_t i = v ^ value2id(xor_val, height);
            id_t child_id = get_child_id(cur, i);
            if (child_id == EMPTY_NODE) continue;
            id_t child_count = get_count(child_id);
            if (cnt < child_count) return {i, v};
            cnt -= child_count;
        }
        assert(false);
    }

    id_t add_empty_node() {
        id_t new_id = nodes.size();
        nodes.emplace_back();
        return new_id;
    }

    static id_t value2id(value_t x, id_t height) {
        return (x >> height) & (NUM_CHILDREN - 1);
    }

    static value_t id2value(id_t x, id_t height) {
        return static_cast<value_t>(x) << height;
    }

    constexpr void check_constants() {
        static_assert(NUM_BITS % LOG_NUM_CHILDREN == 0);
    }
};