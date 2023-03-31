#include <bitset>
#include <cassert>
#include <utility>
#include <vector>

class MatrixBool {
    using MatrixRow = std::bitset<320>;

    const int _rows, _cols;
    std::vector<MatrixRow> _data;

   public:
    MatrixBool(int rows, int cols) : _rows(rows), _cols(cols), _data(rows) {
        assert(rows > 0);
        assert(cols > 0);
        assert(cols < static_cast<int>(_data[0].size()));
    }

    int rows() const { return _rows; }
    int cols() const { return _cols; }

    const bool operator()(int r, int c) const { return _data[r][c]; }
    MatrixRow::reference operator()(int r, int c) { return _data[r][c]; }

    MatrixBool operator~() const {
        MatrixBool ret(_rows, _cols);
        for (int i = 0; i < _rows; ++i) {
            ret._data[i] = ~_data[i];
        }
        return ret;
    }

    MatrixBool& operator&=(const MatrixBool& rhs) {
        assert(_rows == rhs._rows);
        assert(_cols == rhs._cols);
        for (int i = 0; i < _rows; ++i) {
            this->_data[i] &= _data[i];
        }
        return *this;
    }

    MatrixBool& operator|=(const MatrixBool& rhs) {
        assert(_rows == rhs._rows);
        assert(_cols == rhs._cols);
        for (int i = 0; i < _rows; ++i) {
            this->_data[i] |= _data[i];
        }
        return *this;
    }

    MatrixBool& operator^=(const MatrixBool& rhs) {
        assert(_rows == rhs._rows);
        assert(_cols == rhs._cols);
        for (int i = 0; i < _rows; ++i) {
            this->_data[i] ^= _data[i];
        }
        return *this;
    }

    const MatrixRow& operator[](int r) const { return _data[r]; }
    MatrixRow& operator[](int r) { return _data[r]; }
};

MatrixBool operator&(const MatrixBool& lhs, const MatrixBool& rhs) {
    return MatrixBool(lhs) &= rhs;
}

MatrixBool operator|(const MatrixBool& lhs, const MatrixBool& rhs) {
    return MatrixBool(lhs) |= rhs;
}

MatrixBool operator^(const MatrixBool& lhs, const MatrixBool& rhs) {
    return MatrixBool(lhs) ^= rhs;
}

MatrixBool operator*(const MatrixBool& lhs, const MatrixBool& rhs) {
    assert(lhs.cols() == rhs.rows());
    MatrixBool mul(lhs.rows(), rhs.cols());

    for (int i = 0; i < lhs.rows(); ++i) {
        for (int k = 0; k < lhs.cols(); ++k) {
            if (lhs(i, k)) {
                mul[i] ^= rhs[k];
            }
        }
    }

    return mul;
}

// 入力行列を階段行列に変形し，行列のランクを出力する．
int row_reduction(MatrixBool& mat) {
    int r = 0;
    for (int c = 0; c < mat.cols(); ++c) {
        int r_nonzero = r;
        while (r_nonzero < mat.rows() && !mat(r_nonzero, c)) {
            ++r_nonzero;
        }
        if (r_nonzero == mat.rows()) {
            continue;
        }
        if (r_nonzero != r) {
            std::swap(mat[r], mat[r_nonzero]);
        }

        for (int r_dst = r + 1; r_dst < mat.rows(); ++r_dst) {
            if (mat(r_dst, c)) {
                mat[r_dst] ^= mat[r];
            }
        }
        ++r;
        if (r >= mat.rows()) {
            return r;
        }
    }
    return r;
}