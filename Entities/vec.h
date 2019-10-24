//
// Created by Yakimov on 10.10.2019.
//

#ifndef GLASSYRENDER_VEC_H
#define GLASSYRENDER_VEC_H

#include <ostream>
#include <cmath>
#include "point.h"

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

    explicit vec(const VEC &v);

    explicit vec(const point<dim, number_t> &p);

    explicit vec(const point<dim, number_t> &p1, const point<dim, number_t> &p2);

    vec(std::initializer_list<number_t> values);

    ~vec();

    [[nodiscard]] float norm() const;

    [[nodiscard]] VEC normalize() const;

    [[nodiscard]] point<dim, number_t> to_point() const;

    vec<dim + 1, number_t> extend(number_t value) const;

    vec<dim - 1, number_t> shrink() const;

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
    friend VEC operator-(VEC lhs, const VEC &rhs);

    template<size_t N, typename num_t>
    friend VEC operator*(VEC lhs, float a);

    template<size_t N, typename num_t>
    friend VEC operator*(float a, VEC lhs);

    template<size_t N, typename num_t>
    friend VEC operator/(VEC lhs, float a);

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

    friend std::ostream &operator<<(std::ostream &os, const vec &vec) {
        for (size_t i = 0; i < dim; i++) {
            os << vec.coords[i] << " ";
        }
        return os;
    }
};

typedef vec<4, float> vec4f;
typedef vec<3, float> vec3f;
typedef vec<2, size_t> vec2i;

template<size_t dim, typename number_t>
VEC::vec(const VEC &v) {
    for (size_t i = dim; i--;) {
        (*this)[i] = v.coords[i];
    }
}

template<size_t dim, typename number_t>
VEC::vec(const point<dim, number_t> &p1, const point<dim, number_t> &p2) {
    for (size_t i = dim; i--;) {
        this->coords[i] = p2[i] - p1[i];
    }
}

template<size_t dim, typename number_t>
VEC::~vec() {

}

template<size_t dim, typename number_t>
float VEC::norm() const {
    return (std::sqrt((*this) * (*this)));
}

template<size_t dim, typename number_t>
float operator*(const VEC &lhs, const VEC &rhs) {
    float sum = 0;
    for (size_t i = dim; i--;) {
        sum = sum + lhs[i] * rhs[i];
    }
    return sum;
}

template<size_t dim, typename number_t>
VEC operator*(VEC lhs, float a) {
    for (size_t i = dim; i--;) {
        lhs[i] = static_cast<number_t>(lhs[i] * a);
    }
    return lhs;
}

template<size_t dim, typename number_t>
VEC operator*(float a, VEC rhs) {
    for (size_t i = dim; i--;) {
        rhs[i] = static_cast<number_t>(rhs[i] * a);
    }
    return rhs;
}

template<size_t dim, typename number_t>
VEC operator+(VEC lhs, const VEC &rhs) {
    for (size_t i = dim; i--;) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<size_t dim, typename number_t>
VEC operator-(VEC lhs, const VEC &rhs) {
    for (size_t i = dim; i--;) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template<size_t dim, typename number_t>
VEC operator/(VEC lhs, float a) {
    for (size_t i = dim; i--;) {
        lhs[i] = static_cast<number_t>(lhs[i] / a);
    }
    return lhs;
}

template<size_t dim, typename number_t>
VEC vec<dim, number_t>::normalize() const {
    return (*this) / this->norm();
}

template<size_t dim, typename number_t>
vec<dim, number_t>::vec(std::initializer_list<number_t> values) {
    auto it = values.end();
    for (size_t i = dim; i--;) {
        this->coords[i] = *(--it);
    }
}

template<size_t dim, typename number_t>
point<dim, number_t> vec<dim, number_t>::to_point() const {
    return point3f{coords[0], coords[1], coords[2]};
}

template<size_t dim, typename number_t>
vec<dim - 1, number_t> vec<dim, number_t>::shrink() const {
    vec<dim - 1, number_t> res;
    const number_t last = coords[dim - 1];
    for (size_t i = dim - 1; i--;) {
        res[i] = coords[i];
    }
    return res;
}

template<size_t dim, typename number_t>
vec<dim + 1, number_t> vec<dim, number_t>::extend(number_t value) const {
    vec<dim + 1, number_t> res;
    for (size_t i = dim; i--;) {
        res[i] = coords[i];
    }
    res[dim] = value;
    return res;
}

template<size_t dim, typename number_t>
vec<dim, number_t>::vec(const point<dim, number_t> &p) {
    for (size_t i = dim; i--;) {
        coords[i] = p[i];
    }
}




#endif //GLASSYRENDER_VEC_H
