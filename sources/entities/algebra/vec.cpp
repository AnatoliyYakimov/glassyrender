//
// Created by Yakimov on 25.10.2019.
//
#ifndef GLASSYRENDER_vec_H
#include "../../../include/entities/algebra/vec.h"
#endif //GLASSYRENDER_vec_H

template<size_t dim, typename number_t>
inline COLORREF vec<dim,number_t>::get_color_ref() {
    return RGB(255 * coords[0], 255 * coords[1], 255 * coords[2]);
}

template<size_t dim, typename number_t>
vec<dim,number_t>::vec(const vec<dim,number_t> &v) : coords() {
    for (size_t i = dim; i--;) {
        coords[i] = v.coords[i];
    }
}

template<size_t dim, typename number_t>
vec<dim, number_t>::vec(const float &val) {
    for (size_t i = dim; i--;) {
        coords[i] = val;
    }
}

template<size_t dim, typename number_t>
float vec<dim,number_t>::norm() const {
    return (std::sqrt((*this) * (*this)));
}

template<size_t dim, typename number_t>
float operator*(const vec<dim,number_t> &lhs, const vec<dim,number_t> &rhs) {
    float sum = 0;
    for (size_t i = dim; i--;) {
        sum = sum + lhs[i] * rhs[i];
    }
    return sum;
}

template<size_t dim, typename number_t>
vec<dim,number_t> operator*(vec<dim,number_t> lhs, float a) {
    for (size_t i = dim; i--;) {
        lhs[i] *= a;
    }
    return lhs;
}

template<size_t dim, typename number_t>
vec<dim,number_t> operator*(float a, vec<dim,number_t> rhs) {
    for (size_t i = dim; i--;) {
        rhs[i] = static_cast<number_t>(rhs[i] * a);
    }
    return rhs;
}

template<size_t dim, typename number_t>
vec<dim,number_t> operator+(vec<dim,number_t> lhs, const vec<dim,number_t> &rhs) {
    for (size_t i = dim; i--;) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<size_t dim, typename number_t>
vec<dim,number_t> operator-(vec<dim,number_t> lhs, const vec<dim,number_t> &rhs) {
    for (size_t i = dim; i--;) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template<size_t dim, typename number_t>
vec<dim,number_t> operator/(vec<dim,number_t> lhs, float a) {
    for (size_t i = dim; i--;) {
        lhs[i] = static_cast<number_t>(lhs[i] / a);
    }
    return lhs;
}

template<size_t dim, typename number_t>
vec<dim,number_t> vec<dim,number_t>::normalize() const {
    return (*this) / this->norm();
}

template<size_t dim, typename number_t>
vec<dim,number_t>::vec(std::initializer_list<number_t> values) {
    assert(values.size() == dim);
    auto it = values.end();
    for (size_t i = dim; i--;) {
        this->coords[i] = *(--it);
    }
}

template<size_t dim, typename number_t>
vec<dim - 1, number_t> vec<dim,number_t>::shrink() const {
    vec<dim - 1, number_t> res;
    const number_t last = coords[dim - 1];
    for (size_t i = dim - 1; i--;) {
        res[i] = coords[i];
    }
    return res;
}

template<size_t dim, typename number_t>
vec<dim + 1, number_t> vec<dim,number_t>::extend(number_t value) const {
    vec<dim + 1, number_t> res;
    for (size_t i = dim; i--;) {
        res[i] = coords[i];
    }
    res[dim] = value;
    return res;
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

template<size_t dim, typename number_t>
vec<dim, number_t> vec<dim, number_t>::mix(vec<dim, number_t> v) const {
    for (size_t i = dim; i--;) {
        v[i] *= coords[i];
    }
    return v;
}



