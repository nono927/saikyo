#include <cassert>
#include <cctype>
#include <iostream>
#include <map>
#include <utility>

class ConvexHullTrick {
   public:
    using data_t = long long;

    ConvexHullTrick() {}

    // 直線 y = a * x + b を追加する。
    void add(data_t a, data_t b) {
        if (auto itr = _lines.find(a); itr != _lines.end()) {
            if (itr->second <= b) return;
            itr->second = b;
        } else {
            // 一旦直線を入れて、削除するかどうか決める
            _lines[a] = b;
            auto itr1 = _lines.find(a);
            if (should_delete(itr1)) {
                _lines.erase(itr1);
                return;
            }
        }

        // 左を消す
        while (!_lines.empty()) {
            auto itr = _lines.lower_bound(a);
            if (itr == _lines.begin()) break;
            --itr;
            if (!should_delete(itr)) break;
            _lines.erase(itr);
        }

        // 右を消す
        while (!_lines.empty()) {
            auto itr = _lines.upper_bound(a);
            if (!should_delete(itr)) break;
            _lines.erase(itr);
        }
    }

    // 追加した直線の集合のうち、a_i * x + b_i を最小にする (a_i, b_i) を返す。
    // 直線が1つもない場合はassertを発生させる。
    std::pair<data_t, data_t> argmin(data_t x) const {
        assert(!_lines.empty());

        data_t al = _lines.begin()->first;
        data_t ar = (--_lines.end())->first;
        if (binsearch_cond(al, x)) {
            return *_lines.begin();
        }

        while (ar - al > 1) {
            data_t am = (al + ar) / 2;
            if (binsearch_cond(am, x)) {
                ar = am;
            } else {
                al = am;
            }
        }

        return *_lines.lower_bound(ar);
    }

    // 追加した直線の集合に対して、min_i { y = a_i * x + b_i } を求める。
    // 直線が1つもない場合はassertを発生させる。
    data_t min(data_t x) {
        auto [a, b] = argmin(x);
        return a * x + b;
    }

    // 追加した直線の集合を返す。
    // ただし、キーが直線の傾き、値が直線のy切片である。
    std::map<data_t, data_t> lines() { return _lines; }

   private:
    std::map<data_t, data_t> _lines;

    bool should_delete(std::map<data_t, data_t>::const_iterator itr) {
        if (itr == _lines.begin() || itr == _lines.end()) return false;

        auto [a1, b1] = *itr;
        ++itr;
        if (itr == _lines.end()) return false;
        auto [a2, b2] = *itr;
        --itr, --itr;
        auto [a0, b0] = *itr;

        return (b0 - b1) * (a1 - a2) >= (b1 - b2) * (a0 - a1);
    }

    bool binsearch_cond(data_t a, data_t x) const {
        auto itr = _lines.lower_bound(a);
        assert(itr != _lines.end());
        auto [a0, b0] = *itr;
        ++itr;
        if (itr == _lines.end()) return true;
        auto [a1, b1] = *itr;
        return a0 * x + b0 <= a1 * x + b1;
    }
};