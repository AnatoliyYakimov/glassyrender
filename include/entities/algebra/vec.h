//
// Created by Yakimov on 10.10.2019.
//

#ifndef GLASSYRENDER_VEC_H
#define GLASSYRENDER_VEC_H

#include <ostream>
#include <cmath>
#include "point.h"
#include <cassert>

#define VEC vec<dim,number_t>

/**
 * Класс, реализующий функционал вектора линейной алгебры.
 * @tparam dim - размерность ветора
 * @tparam number_t - тип хранимого значения
 */
template<size_t dim, typename number_t>
class vec {
public:

    number_t coords[dim];

    vec() = default;

    vec(const VEC &v);

    explicit vec(const point<dim, number_t> &p);

    explicit vec(const point<dim, number_t> &p1, const point<dim, number_t> &p2);

    explicit vec(const float &val);

    vec(std::initializer_list<number_t> values);

    ~vec();

    [[nodiscard]] float norm() const;

    [[nodiscard]] VEC normalize() const;

    [[nodiscard]] VEC mix(VEC v) const;

    [[nodiscard]] point<dim, number_t> to_point() const;

    vec<dim + 1, number_t> extend(number_t value) const;

    vec<dim - 1, number_t> shrink() const;

    inline COLORREF get_color_ref();

    vec<dim, number_t> pow(float a) const;

    template<size_t N, typename num_t>
    friend vec<N, num_t> exp(vec<N, num_t> v);

    /**
     * Скалярное произведение векторов.
     * @tparam N - размерность
     * @tparam num_t - тип хранимых значений
     * @param v1 - вектор
     * @param v2 - вектор
     * @return - скалярное произведение векторов
     */
    template<size_t N, typename num_t>
    friend float operator*(const VEC &v1, const VEC &v2);

    template<size_t N, typename num_t>
    friend VEC operator+(VEC lhs, const VEC &rhs);

    template<size_t N, typename num_t>
    friend VEC operator+(float a, VEC rhs);

    template<size_t N, typename num_t>
    friend VEC operator-(VEC lhs, const VEC &rhs);

    template<size_t N, typename num_t>
    friend VEC operator*(VEC lhs, float a);

    template<size_t N, typename num_t>
    friend VEC operator*(float a, VEC lhs);

    template<size_t N, typename num_t>
    friend VEC operator/(VEC lhs, float a);

    template<size_t N, typename num_t>
    friend VEC operator/(VEC lhs, const VEC& rhs);

    bool operator==(const VEC &rhs) const {
        bool equals = true;
        for (size_t i = dim; i-- && equals;) {
            equals = rhs.coords[i] == this->coords[i];
        }
        return equals;
    }

    const number_t &operator[](const size_t idx) const {
        return this->coords[idx];
    }

    number_t &operator[](const size_t idx) {
        return this->coords[idx];
    }

    vec<dim, number_t> operator-() const {
        return -1.0 * vec<dim, number_t>(*this);
    }

    friend std::ostream &operator<<(std::ostream &os, const vec &vec) {
        for (size_t i = 0; i < dim; i++) {
            os << vec.coords[i] << " ";
        }
        return os;
    }
};



typedef vec<3, float> vec3f;
typedef vec<2, float> vec2f;


#include "../../../sources/entities/algebra/vec.cpp"

#endif //GLASSYRENDER_VEC_H
