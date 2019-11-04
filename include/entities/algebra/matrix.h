//
// Created by Yakimov on 16.10.2019.
//

#ifndef GLASSYRENDER_MATRIX_H
#define GLASSYRENDER_MATRIX_H

#include <cstddef>
#include <cassert>
#include <ostream>
#include "vec.h"

#define MATRIX matrix<row_size, col_size, number_t>
        

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

    static MATRIX identity();

    vec<row_size, number_t> column(size_t idx) const;

    matrix<col_size, row_size, number_t> transpose() const;

    matrix<col_size, row_size, number_t> inverse() const;

    // Алгебраическое дополнение
    number_t get_cofactor(size_t row, size_t col) const;

    matrix<row_size - 1, col_size - 1, number_t> get_minor(size_t row, size_t col) const;

    number_t determinant() const;

    MATRIX union_matrix() const;

    const vec<col_size, number_t> &operator[](size_t idx) const {
        assert(idx < row_size);
        return rows[idx];
    }

    vec<col_size, number_t> &operator[](size_t idx) {
        assert(idx < row_size);
        return rows[idx];
    }

    template<size_t N, size_t M, size_t K, typename num>
    friend inline matrix<N, M, num> operator*(const matrix<N, K, num> &lhs, const matrix<K, M, num> &rhs);

    template<size_t N, size_t M, typename num>
    friend inline matrix<N, M, num> operator*(const matrix<N, M, num> &lhs, num a);

    template<size_t N, size_t M, typename num>
    friend inline matrix<N, M, num> operator*(num a, const matrix<N, M, num> &rhs);

    template<size_t N, size_t M, typename num>
    friend inline vec<N, num> operator*(const matrix<N, M, num> &lhs, const vec<M, num> &rhs);

    template<size_t N, size_t M, typename num>
    friend inline point<N, num> operator*(const matrix<N, M, num> &lhs, const point<M, num> &rhs);

    template<size_t N, size_t M, typename num>
    friend inline matrix<N, M, num> operator/(const matrix<N, M, num> &lhs, num a);

    template<typename num>
    friend inline vec<3, num> operator*(const matrix<4, 4, num> &mat, const vec<3, num> &v);

    template<typename num>
    friend inline point<3, num> operator*(const matrix<4, 4, num> &mat, const point<3, num> &p);

    friend std::ostream &operator<<(std::ostream &os, const matrix &matrix) {
        for (size_t i = 0; i < row_size; i++) {
            os << matrix.rows[i] << "\n";
        }
        return os;
    }
};

#include "../../../sources/entities/algebra/matrix.cpp"

#endif //GLASSYRENDER_MATRIX_H
