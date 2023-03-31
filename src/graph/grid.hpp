#include <cassert>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

template <class T>
class Grid {
    const int _rows, _cols;
    std::unique_ptr<T[]> _data;

   public:
    Grid(int rows, int cols)
        : _rows(rows), _cols(cols), _data(new T[rows * cols]) {
        assert(rows > 0);
        assert(cols > 0);
    }

    Grid(std::vector<std::vector<T>>& vec) {
        assert(!vec.empty());
        assert(!vec[0].empty());
        _rows = vec.size();
        _cols = vec[0].size();
        _data.reset(new T[_rows * _cols]);
        int offset = 0;
        for (auto&& v : vec) {
            assert(v.size() == _cols);
            std::memmove(_data.get() + offset, v.data(), sizeof(T) * _cols);
            offset += _cols;
        }
    }

    Grid(Grid<T>& other)
        : _rows(other.rows()),
          _cols(other.cols()),
          _data(new T[_rows * _cols]) {
        std::memmove(_data.get(), other._data.get(), sizeof(T) * _rows * _cols);
    }

    int rows() { return _rows; }
    int cols() { return _cols; }

    bool is_valid_loc(int i, int j) {
        return (i >= 0) && (i < _rows) && (j >= 0) && (j < _cols);
    }

    int to_loc1d(int i, int j) {
        assert(is_valid_loc(i, j));
        return i * _cols + j;
    }

    std::pair<int, int> to_loc2d(int k) {
        assert(k >= 0 && k < _cols * _rows);
        return {k / _cols, k % _cols};
    }

    T& operator()(int i, int j) {
        assert(is_valid_loc(i, j));
        return _data[to_loc1d(i, j)];
    }

    std::vector<std::pair<int, int>> neighbors(int i, int j) {
        constexpr std::array<int, 4> delta_i = {1, 0, -1, 0};
        constexpr std::array<int, 4> delta_j = {0, 1, 0, -1};
        std::vector<std::pair<int, int>> _neighbors;
        for (int k = 0; k < 4; ++k) {
            int x = i + delta_i[k];
            int y = j + delta_j[k];
            if (is_valid_loc(x, y)) {
                _neighbors.emplace_back(x, y);
            }
        }
        return _neighbors;
    }

    void dump() {
        std::cerr << "{";
        for (int i = 0; i < _rows; ++i) {
            std::cerr << "{";
            for (int j = 0; j < _cols; ++j) {
                std::cerr << _data[to_loc1d(i, j)] << ", ";
            }
            std::cerr << "\e[2D}, ";
        }
        std::cerr << "\e[2D}";
    }
};