#pragma once

#include <cassert>
#include <functional>
#include <vector>

// 常に値がソートされている配列のクラス．
// 定数時間のランダムアクセス，線形時間の要素追加をサポートする．
template <class T, class Compare = std::less<T>>
class SortedArray {
    std::vector<T> _data;
    T empty_val;
    const Compare comp;
    const int _capacity;

   public:
    SortedArray(int capacity) : _data(), _capacity(capacity), comp() {
        assert(capacity > 0);
    }

    // i番目の要素にアクセスする．
    const T operator[](size_t i) const {
        assert(i < _data.size());
        return _data[i];
    }

    // 要素valを配列に追加する．
    // 時間計算量はデータ数に比例する．
    void insert(T val) {
        size_t pos = 0;
        while (pos < _data.size() && comp(_data[pos], val)) {
            ++pos;
        }

        if (pos == _data.size()) {
            if (pos < _capacity) {
                _data.emplace_back(val);
            }
            return;
        }

        if (_data.size() < (size_t)_capacity) {
            _data.emplace_back(T());
        }
        for (size_t i = _data.size() - 1; i > pos; --i) {
            _data[i] = _data[i - 1];
        }
        _data[pos] = val;
    }

    template <class... Args>
    void emplace(Args&&... args) {
        insert(T(std::forward<Args>(args)...));
    }

    size_t size() const { return _data.size(); }
    size_t capacity() const { return _capacity; }
    typename std::vector<T>::const_iterator begin() { return _data.begin(); }
    typename std::vector<T>::const_iterator end() { return _data.end(); }
};