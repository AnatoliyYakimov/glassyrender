//
// Created by Yakimov on 16.10.2019.
//

#ifndef GLASSYRENDER_MATRIX_H
#define GLASSYRENDER_MATRIX_H

#include <cstddef>
#include <cassert>
#include <ostream>
#include "vec.h"



/**
 * Класс матриц.
 * @tparam row_size - Rows (число строк)
 * @tparam col_size - Columns (число столбцов)
 * @tparam number_t
 */
template<size_t row_size, size_t col_size, typename number_t>
class matrix {
protected:
    vec<col_size, number_t> rows[row_size];
public:

    matrix() = default;

    matrix(std::initializer_list<vec<col_size, number_t>> initializer_list);

    matrix(std::initializer_list<number_t> initializer_list);

    vec<row_size, number_t> column(size_t idx) const;

    matrix<col_size, row_size, number_t> transpose() const;

    matrix<col_size, row_size, number_t> inverse() const;

    // Алгебраическое дополнение
    number_t get_cofactor(size_t row, size_t col) const;

    matrix<row_size - 1, col_size - 1, number_t> get_minor(size_t row, size_t col) const;

    number_t determinant() const;

    matrix<row_size, col_size, number_t> union_matrix() const;

    const ROW &operator[](size_t idx) const {
        assert(idx < row_size);
        return rows[idx];
    }

    ROW &operator[](size_t idx) {
        assert(idx < row_size);
        return rows[idx];
    }

    template<size_t N, size_t M, size_t K, typename num>
    friend inline matrix<N, M, num> operator*(const matrix<N, K, num> &lhs, const matrix<K, M, num> &rhs);
    template<size_t N, size_t M, typename num>
    friend inline matrix<N, M, num> operator*(const matrix<N, M, num> &lhs, num a);
    template<size_t N, size_t M, typename num>
    friend inline matrix<N, M, num> operator/(const matrix<N, M, num> &lhs, num a);

    friend std::ostream &operator<<(std::ostream &os, const matrix &matrix) {
        for (size_t i = 0; i < row_size; i++) {
            os << matrix.rows[i] << "\n";
        }
        return os;
    }
};

template<size_t dim, typename number_t>
class dt {
public:
    static number_t det(const matrix<dim, dim, number_t> &mat) {
        number_t ret = 0;
        for (size_t i = dim; i--;) {
            ret += mat[0][i] + mat.get_cofactor(0, i);
        }
        return ret;
    }
};

template<typename number_t>
class dt<1, number_t> {
public:
    static number_t det(const matrix<1, 1, number_t> &mat) {
            return mat[0][0];
    }
};

template<size_t row_size, size_t col_size, typename number_t>
matrix<row_size, col_size, number_t>::matrix(std::initializer_list<number_t> initializer_list) {
    auto it = initializer_list.end();
    for (size_t i = row_size; i--;) {
        vec<col_size, number_t> v;
        for (size_t j = col_size; j--;) {
            v[j] = *(--it);
        }
        rows[i] = v;
    }
}

template<size_t row_size, size_t col_size, typename number_t>
matrix<row_size, col_size, number_t>::matrix(std::initializer_list<vec<col_size, number_t>> initializer_list) {
    auto it = initializer_list.end();
    for (size_t i = row_size; i--;) {
        rows[i] = *(--it);
    }
}

template<size_t row_size, size_t col_size, typename number_t>
vec<row_size, number_t> matrix<row_size, col_size, number_t>::column(size_t idx) const {
    assert(idx < col_size);
    vec<row_size, number_t> col;
    for (size_t i = row_size; i--;) {
        col[i] = rows[i][idx];
    }
    return col;
}

template<size_t N, size_t M, size_t K, typename num>
inline matrix<N, M, num> operator*(const matrix<N, K, num> &lhs, const matrix<K, M, num> &rhs) {
    matrix<N, M, num> res;
    matrix<M, K, num> rhs_cols;
    for (size_t k = M; k--;) {
        rhs_cols[k] = rhs.column(k);
    }
    for (size_t i = N; i--;) {
        vec<M, num> v;
        for (size_t j = M; j--;) {
            v[j] = lhs[i] * rhs_cols[j];
        }
        res[i] = v;
    }
    return res;
}

template<size_t row_size, size_t col_size, typename number_t>
number_t matrix<row_size, col_size, number_t>::determinant() const {
    static_assert(row_size == col_size);
    return dt<row_size, number_t>::det(*this);
}

template<size_t row_size, size_t col_size, typename number_t>
matrix<row_size - 1, col_size - 1, number_t> matrix<row_size, col_size, number_t>::get_minor(size_t row, size_t col) const {
    static_assert(row_size == col_size);

    matrix<row_size - 1, col_size - 1, number_t> res;
    for (size_t i = row_size - 1; i--;) {
        for (size_t j = col_size - 1; j--;) {
            res[i][j] = rows[i < row ? i : i + 1][j < col ? j : j + 1];
        }
    }
    return res;
}

template<size_t row_size, size_t col_size, typename number_t>
number_t matrix<row_size, col_size, number_t>::get_cofactor(size_t row, size_t col) const {
    static_assert(row_size == col_size);
    return get_minor(row, col).determinant() * ((row + col) % 2 ? -1 : 1);
}

template<size_t row_size, size_t col_size, typename number_t>
matrix<row_size, col_size, number_t> matrix<row_size, col_size, number_t>::union_matrix() const {
    static_assert(row_size == col_size);
    matrix<row_size, col_size, number_t> res;
    for (size_t i = row_size; i--;) {
        for (size_t j = col_size; j--;) {
            res[i][j] = get_cofactor(i, j);
        }
    }
    return res;
}

template<size_t row_size, size_t col_size, typename number_t>
matrix<col_size, row_size, number_t> matrix<row_size, col_size, number_t>::inverse() const {
    static_assert(row_size == col_size);

    matrix<col_size, row_size, number_t> res = union_matrix();
    // умножаем скалярно строку на вектор её алгебраических дополнений
    number_t det = rows[0] * res[0];

    return res.transpose() / det;
}

template<size_t row_size, size_t col_size, typename number_t>
matrix<col_size, row_size, number_t> matrix<row_size, col_size, number_t>::transpose() const {
    matrix<col_size, row_size, number_t> res;
    for (size_t i = row_size; i--;) {
        res[i] = column(i);
    }
    return res;
}

template<size_t N, size_t M, typename num>
matrix<N, M, num> operator*(const matrix<N, M, num> &lhs, num a) {
    matrix<N, M, num> res;
    for (size_t i = N; i--;) {
        res = lhs[i] * a;
    }
    return res;
}

template<size_t N, size_t M, typename num>
matrix<N, M, num> operator/(const matrix<N, M, num> &lhs, num a) {
    matrix<N, M, num> res;
    for (size_t i = N; i--;) {
        res[i] = lhs[i] / a;
    }
    return res;
}

#endif //GLASSYRENDER_MATRIX_H
