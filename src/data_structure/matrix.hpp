#include <cassert>
#include <vector>

// 要素の型がTの行列クラス
template <class T>
class Matrix {
    int _rows, _cols;
    std::vector<T> _data;

    bool check_range(int r, int c) const {
        return r >= 0 && r < _rows && c >= 0 && c < _cols;
    }

   public:
    Matrix<T>(int rows, int cols)
        : _rows(rows), _cols(cols), _data(rows * cols){};

    Matrix<T>(const std::vector<std::vector<T>>&& data) {
        assert(!data.empty());
        assert(!data[0].empty());

        _rows = data.size();
        _cols = data[0].size();
        _data.resize(_rows * _cols);

        std::size_t k = 0;
        for (std::size_t i = 0; i < _rows; ++i) {
            assert(data[i].size() == _cols);
            for (std::size_t j = 0; j < _cols; ++j) {
                _data[k++] = data[i][j];
            }
        }
    }

    T& operator()(int r, int c) {
        assert(check_range(r, c));
        return _data[r * _cols + c];
    }

    const T& operator()(int r, int c) const {
        assert(check_range(r, c));
        return _data[r * _cols + c];
    }

    int rows() const { return _rows; }
    int cols() const { return _cols; }

    Matrix<T> operator+() const { return Matrix<T>(*this); }

    Matrix<T> operator-() const {
        Matrix ret(*this);
        for (auto&& x : ret._data) {
            x = -x;
        }
        return ret;
    }

    Matrix<T>& operator+=(const T& rhs) {
        for (std::size_t i = 0; i < _data.size(); ++i) {
            _data[i] += rhs;
        }
        return *this;
    }

    Matrix<T>& operator+=(const Matrix<T>& rhs) {
        assert(_rows == rhs._rows);
        assert(_cols == rhs._cols);
        for (std::size_t i = 0; i < _data.size(); ++i) {
            _data[i] += rhs._data[i];
        }
        return *this;
    }

    Matrix<T>& operator-=(const T& rhs) { return (*this) += (-rhs); }

    Matrix<T>& operator-=(const Matrix<T>& rhs) {
        assert(_rows == rhs.rows());
        assert(_cols == rhs.cols());
        for (std::size_t i = 0; i < _data.size(); ++i) {
            _data[i] -= rhs._data[i];
        }
        return *this;
    }

    Matrix<T>& operator*=(const T& rhs) {
        for (std::size_t i = 0; i < _data.size(); ++i) {
            _data[i] *= rhs;
        }
        return *this;
    }

    static Matrix<T> unit(const int size) {
        Matrix<T> ret(size, size);
        for (int i = 0; i < size; ++i) {
            // 単位元が1でない場合は，ここを直接書き換える
            ret(i, i) = 1;
        }
        return ret;
    }

    Matrix<T> pow(long long n) const {
        assert(_rows == _cols);
        Matrix<T> ret = unit(_rows);
        Matrix<T> m(*this);
        while (n > 0) {
            if (n & 1LL) {
                ret = ret * m;
            }
            m = m * m;
            n >>= 1;
        }
        return ret;
    }

    template <class U>
    friend bool operator==(const Matrix<U>& lhs, const Matrix<U>& rhs);
};

template <class T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return lhs._rows == rhs._rows && lhs._cols == rhs._cols &&
           lhs._data == rhs._data;
}

template <class T>
bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return !(lhs == rhs);
}

template <class T>
Matrix<T> operator+(const Matrix<T>& lhs, const T& rhs) {
    return Matrix<T>(lhs) += rhs;
}

template <class T>
Matrix<T> operator+(const T& lhs, const Matrix<T>& rhs) {
    return rhs + lhs;
}

template <class T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return Matrix<T>(lhs) += rhs;
}

template <class T>
Matrix<T> operator-(const Matrix<T>& lhs, const T& rhs) {
    return Matrix<T>(lhs) -= rhs;
}

template <class T>
Matrix<T> operator-(const T& lhs, const Matrix<T>& rhs) {
    return -Matrix<T>(rhs) += lhs;
}

template <class T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return Matrix<T>(lhs) -= rhs;
}

template <class T>
Matrix<T> operator*(const Matrix<T>& lhs, const T& rhs) {
    return Matrix<T>(lhs) *= rhs;
}

template <class T>
Matrix<T> operator*(const T& lhs, const Matrix<T>& rhs) {
    return rhs * lhs;
}

template <class T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    assert(lhs.cols() == rhs.rows());
    Matrix<T> ret(lhs.rows(), rhs.cols());
    for (int i = 0; i < lhs.rows(); ++i) {
        for (int k = 0; k < lhs.cols(); ++k) {
            for (int j = 0; j < rhs.cols(); ++j) {
                ret(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
    return ret;
}
