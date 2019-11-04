//
// Created by Yakimov on 25.10.2019.
//

#ifndef GLASSYRENDER_MATRIX_H
#include "../../include/entities/matrix.h"
#endif //GLASSYRENDER_MATRIX_H

/**
 * Утилитарный класс для реализации метода determinant(). Имеет 2 спецификации метода det:
 * для размерности > 1
 * для размерности = 1
 * @tparam dim
 * @tparam number_t
 */
template<size_t dim, typename number_t>
class dt {
public:
    static number_t det(const matrix<dim, dim, number_t> &mat) {
        number_t ret = 0;
        for (size_t i = dim; i--;) {
            ret += mat[0][i] * mat.get_cofactor(0, i);
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
MATRIX::matrix(std::initializer_list<number_t> initializer_list) {
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
MATRIX::matrix(std::initializer_list<vec<col_size, number_t>> initializer_list) {
    auto it = initializer_list.end();
    for (size_t i = row_size; i--;) {
        rows[i] = vec<col_size, number_t>(*(--it));
    }
}

template<size_t row_size, size_t col_size, typename number_t>
vec<row_size, number_t> MATRIX::column(size_t idx) const {
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
number_t MATRIX::determinant() const {
    static_assert(row_size == col_size);
    return dt<row_size, number_t>::det(*this);
}

template<size_t row_size, size_t col_size, typename number_t>
matrix<row_size - 1, col_size - 1, number_t>
MATRIX::get_minor(size_t row, size_t col) const {
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
number_t MATRIX::get_cofactor(size_t row, size_t col) const {
    static_assert(row_size == col_size);
    return get_minor(row, col).determinant() * ((row + col) % 2 ? -1 : 1);
}

template<size_t row_size, size_t col_size, typename number_t>
MATRIX MATRIX::union_matrix() const {
    static_assert(row_size == col_size);
    MATRIX res;
    for (size_t i = row_size; i--;) {
        for (size_t j = col_size; j--;) {
            res[i][j] = get_cofactor(i, j);
        }
    }
    return res;
}

template<size_t row_size, size_t col_size, typename number_t>
matrix<col_size, row_size, number_t> MATRIX::inverse() const {
    static_assert(row_size == col_size);

    matrix<col_size, row_size, number_t> res = union_matrix();
    // умножаем скалярно строку на вектор её алгебраических дополнений
    number_t det = rows[0] * res[0];

    return res.transpose() / det;
}

template<size_t row_size, size_t col_size, typename number_t>
matrix<col_size, row_size, number_t> MATRIX::transpose() const {
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
        res[i] = lhs[i] * a;
    }
    return res;
}

template<size_t N, size_t M, typename num>
matrix<N, M, num> operator*(num a, const matrix<N, M, num> & rhs) {
    return rhs * a;
}


template<size_t N, size_t M, typename num>
matrix<N, M, num> operator/(const matrix<N, M, num> &lhs, num a) {
    matrix<N, M, num> res;
    for (size_t i = N; i--;) {
        res[i] = lhs[i] / a;
    }
    return res;
}

template<size_t N, size_t M, typename num>
vec<N, num> operator*(const matrix<N, M, num> &lhs, const vec<M, num> &rhs) {
    vec<N, num> res;
    for (size_t i = N; i--;) {
        res[i] = lhs[i] * rhs;
    }
    return res;
}

template<size_t N, size_t M, typename num>
point<N, num> operator*(const matrix<N, M, num> &lhs, const point<M, num> &rhs) {
    return lhs * vec<N, num>(rhs);
}

template<typename num>
vec<3, num> operator*(const matrix<4, 4, num> &mat, const vec<3, num> &v) {
    vec<4 , num> res = v.extend(1);
    res = mat * res;
    return res.shrink() / res[3];
}

template<typename num>
point<3, num> operator*(const matrix<4, 4, num> &mat, const point<3, num> &p) {
    return (mat * vec<3, num>(p)).to_point();
}

template<size_t row_size, size_t col_size, typename number_t>
MATRIX MATRIX::identity() {
    MATRIX res;
    for (size_t i = row_size; i--;) {
        for (size_t j = col_size; j--;) {
            res[i][j] = (i == j);
        }
    }
    return res;
}