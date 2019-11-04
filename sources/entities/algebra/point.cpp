//
// Created by Yakimov on 25.10.2019.
//

#ifndef GLASSYRENDER_POINT_H
#include "../../include/entities/point.h"
#endif //GLASSYRENDER_POINT_H

template<size_t N, typename num>
std::ostream &operator<<(std::ostream &os, const point<N, num> &point) {
    for (size_t i = N; i--;) {
        os << point[i] << " ";
    }
    return os;
}

typedef point<2, float> point2f;
typedef point<2, int> point2i;

template<size_t dim, typename number_t>
POINT::point(const POINT &p) {
    for (size_t i = dim; i--;) {
        this->coords[i] = p[i];
    }
}

template<size_t dim, typename number_t>
point<dim, number_t>::~point() {
}

template<size_t dim, typename number_t>
POINT operator*(POINT lhs, float a) {
    for (size_t i = dim; i--;) {
        lhs[i] = static_cast<number_t>(lhs[i] * a);
    }
    return lhs;
}

template<size_t dim, typename number_t>
POINT operator*(float a, POINT rhs) {
    for (size_t i = dim; i--;) {
        rhs[i] = static_cast<number_t>(rhs[i] * a);
    }
    return rhs;
}

template<size_t dim, typename number_t>
POINT operator+(POINT lhs, const POINT &rhs) {
    for (size_t i = dim; i--;) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<size_t dim, typename number_t>
POINT operator-(POINT lhs, const POINT &rhs) {
    for (size_t i = dim; i--;) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template<size_t dim, typename number_t>
POINT operator/(POINT lhs, const float a) {
    for (size_t i = dim; i--;) {
        lhs[i] = static_cast<number_t>(lhs[i] / a);
    }
    return lhs;
}

template<size_t dim, typename number_t>
point<dim, number_t>::point(std::initializer_list<number_t> values) {
    auto it = values.end();
    for (size_t i = dim; i--;) {
        this->coords[i] = *(--it);
    }
}

template<size_t dim, typename number_t>
point<dim - 1, number_t> point<dim, number_t>::shrink() const {
    point<dim - 1, number_t> res;
    const number_t last = coords[dim - 1];
    for (size_t i = dim - 1; i--;) {
        res[i] = coords[i] / last;
    }
    return res;
}

template<size_t dim, typename number_t>
point<dim + 1, number_t> point<dim, number_t>::extend() const {
    point<dim + 1, number_t> res;
    for (size_t i = dim; i--;) {
        res[i] = coords[i];
    }
    res[dim] = 1;
    return res;
}