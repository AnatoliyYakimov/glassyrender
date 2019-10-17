//
// Created by Yakimov on 16.10.2019.
//

#ifndef GLASSYRENDER_MATRIX_H
#define GLASSYRENDER_MATRIX_H

#include <cstddef>
#include <assert.h>
#include "vec.h"

#define ROW vec<col_size, number_t>

/**
 * Класс матриц.
 * @tparam row_size - Rows (число строк)
 * @tparam col_size - Columns (число столбцов)
 * @tparam number_t
 */
template<size_t row_size, size_t col_size, typename number_t>
class matrix {
protected:
    ROW rows[row_size];
public:

    matrix() = default;

    matrix(std::initializer_list<ROW> rows_list);

    matrix(std::initializer_list<number_t> nums_list);

    vec<row_size, number_t> column(size_t idx) const;

    const ROW &operator[](size_t idx) const {
        assert(idx < row_size);
        return rows[idx];
    }

    ROW &operator[](size_t idx) {
        assert(idx < row_size);
        return rows[idx];
    }

    template<size_t N, size_t M, size_t K, typename num>
    friend matrix<N, M, num> operator*(const matrix<N, K, num> &lhs, const matrix<K, M, num> &rhs);
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
matrix<N, M, num> operator*(const matrix<N, K, num> &lhs, const matrix<K, M, num> &rhs) {
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

#endif //GLASSYRENDER_MATRIX_H
