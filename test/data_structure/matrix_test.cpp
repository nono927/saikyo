#include "data_structure/matrix.hpp"

#include <gtest/gtest.h>

TEST(MatrixTest, Size) {
    Matrix<int> mat(2, 3);
    EXPECT_EQ(mat.rows(), 2);
    EXPECT_EQ(mat.cols(), 3);
}

TEST(MatrixTest, Get) {
    Matrix<int> mat({{1, 2}, {3, 4}});
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(0, 1), 2);
    EXPECT_EQ(mat(1, 0), 3);
    EXPECT_EQ(mat(1, 1), 4);
}

TEST(MatrixTest, Equal) {
    Matrix<int> mat0({{1, 2}, {3, 4}});
    Matrix<int> mat1({{1, 2}, {3, 4}});
    Matrix<int> mat2({{1, 2, 0}, {3, 4, 0}});
    Matrix<int> mat3({{1, 2, 3, 4}});
    Matrix<int> mat4({{1}, {2}, {3}, {4}});
    EXPECT_EQ(mat0 == mat1, true);
    EXPECT_EQ(mat0 == mat2, false);
    EXPECT_EQ(mat0 == mat3, false);
    EXPECT_EQ(mat0 == mat4, false);
}

TEST(MatrixTest, UnaryOp) {
    Matrix<int> mat({{1, 2}, {3, 4}});
    Matrix<int> expect_pos({{1, 2}, {3, 4}});
    Matrix<int> expect_neg({{-1, -2}, {-3, -4}});
    EXPECT_EQ(+mat, expect_pos);
    EXPECT_EQ(-mat, expect_neg);
}

TEST(MatrixTest, BinOpScalar) {
    Matrix<int> mat({{3, 6}, {9, 12}});
    EXPECT_EQ(mat + 1, Matrix<int>({{4, 7}, {10, 13}}));
    EXPECT_EQ(1 + mat, Matrix<int>({{4, 7}, {10, 13}}));
    EXPECT_EQ(mat - 1, Matrix<int>({{2, 5}, {8, 11}}));
    EXPECT_EQ(1 - mat, Matrix<int>({{-2, -5}, {-8, -11}}));
    EXPECT_EQ(mat * 2, Matrix<int>({{6, 12}, {18, 24}}));
    EXPECT_EQ(2 * mat, Matrix<int>({{6, 12}, {18, 24}}));
}

TEST(MatrixTest, BinOpMat) {
    Matrix<int> mat1({{1, 2}, {3, 4}});

    Matrix<int> mat2({{5, 6}, {7, 8}});
    EXPECT_EQ(mat1 + mat2, Matrix<int>({{6, 8}, {10, 12}}));
    EXPECT_EQ(mat1 - mat2, Matrix<int>({{-4, -4}, {-4, -4}}));
    EXPECT_EQ(mat1 * mat2, Matrix<int>({{19, 22}, {43, 50}}));

    Matrix<int> mat3({{1, 2, 3, 4}});
    EXPECT_DEATH(mat1 + mat3, "");
    EXPECT_DEATH(mat1 - mat3, "");
    EXPECT_DEATH(mat1 * mat3, "");
}

TEST(MatrixTest, CompoundAssignmentScalar) {
    Matrix<int> mat({{3, 6}, {9, 12}});

    Matrix<int> mat_add(mat);
    Matrix<int> mat_sub(mat);
    Matrix<int> mat_mul(mat);
    mat_add += 1;
    mat_sub -= 1;
    mat_mul *= 2;

    EXPECT_EQ(mat_add, Matrix<int>({{4, 7}, {10, 13}}));
    EXPECT_EQ(mat_sub, Matrix<int>({{2, 5}, {8, 11}}));
    EXPECT_EQ(mat_mul, Matrix<int>({{6, 12}, {18, 24}}));
}

TEST(MatrixTest, CompoundAssignmentMat) {
    Matrix<int> mat1({{1, 2}, {3, 4}});
    Matrix<int> mat2({{5, 6}, {7, 8}});

    Matrix<int> mat_add(mat1);
    Matrix<int> mat_sub(mat1);
    mat_add += mat2;
    mat_sub -= mat2;

    EXPECT_EQ(mat_add, Matrix<int>({{6, 8}, {10, 12}}));
    EXPECT_EQ(mat_sub, Matrix<int>({{-4, -4}, {-4, -4}}));

    Matrix<int> mat3({{1, 2, 3, 4}});
    EXPECT_DEATH(mat1 += mat3, "");
    EXPECT_DEATH(mat1 -= mat3, "");
}

TEST(MatrixTest, Unit) {
    EXPECT_EQ(Matrix<int>::unit(2), Matrix<int>({{1, 0}, {0, 1}}));
}

TEST(MatrixTest, Pow) {
    Matrix<int> mat({{1, 2}, {3, 4}});
    EXPECT_EQ(mat.pow(3), Matrix<int>({{37, 54}, {81, 118}}));

    Matrix<int> mat_not_square({{1, 2}, {3, 4}, {5, 6}});
    EXPECT_DEATH(mat_not_square.pow(3), "");
}
