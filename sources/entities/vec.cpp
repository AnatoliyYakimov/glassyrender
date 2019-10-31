//
// Created by Yakimov on 25.10.2019.
//

#include "../../include/entities/vec.h"

#ifndef GLASSYRENDER_VEC_H
#include "../../include/entities/vec.h"
#endif //GLASSYRENDER_VEC_H

template<size_t dim, typename number_t>
inline COLORREF VEC::get_color_ref() {
    return RGB(255 * coords[0], 255 * coords[1], 255 * coords[2]);
}

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
VEC VEC::normalize() const {
    return (*this) / this->norm();
}

template<size_t dim, typename number_t>
VEC::vec(std::initializer_list<number_t> values) {
    auto it = values.end();
    for (size_t i = dim; i--;) {
        this->coords[i] = *(--it);
    }
}

template<size_t dim, typename number_t>
point<dim, number_t> VEC::to_point() const {
    return point3f{coords[0], coords[1], coords[2]};
}

template<size_t dim, typename number_t>
vec<dim - 1, number_t> VEC::shrink() const {
    vec<dim - 1, number_t> res;
    const number_t last = coords[dim - 1];
    for (size_t i = dim - 1; i--;) {
        res[i] = coords[i];
    }
    return res;
}

template<size_t dim, typename number_t>
vec<dim + 1, number_t> VEC::extend(number_t value) const {
    vec<dim + 1, number_t> res;
    for (size_t i = dim; i--;) {
        res[i] = coords[i];
    }
    res[dim] = value;
    return res;
}

template<size_t dim, typename number_t>
VEC::vec(const point<dim, number_t> &p) {
    for (size_t i = dim; i--;) {
        coords[i] = p[i];
    }
}

template<size_t dim, typename number_t>
vec<dim, number_t> vec<dim, number_t>::pow(const float a) const {
    vec<dim, number_t> res(*this);
    for (size_t i = dim; i--;) {
        res[i] = std::pow(res[i], a);
    }
    return res;
}

template<size_t dim, typename number_t>
vec<dim, number_t> operator+(float a, vec<dim, number_t> rhs) {
    for (size_t i = dim; i--;) {
        rhs[i] += a;
    }
    return rhs;
}

template<size_t dim, typename number_t>
vec<dim, number_t> operator/(vec<dim, number_t> lhs, const vec<dim, number_t> &rhs) {
    for (size_t i = dim; i--;) {
        lhs[i] /= rhs[i];
    }
    return lhs;
}

template<size_t N, typename num_t>
vec<N, num_t> exp(vec<N, num_t> v) {
    for (size_t i = N; i--;) {
        v[i] = std::exp(v[i]);
    }
    return v;
}

