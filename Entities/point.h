//
// Created by Yakimov on 05.10.2019.
//

#ifndef GLASSYRENDER_POINT_H
#define GLASSYRENDER_POINT_H

#include <ostream>

#define POINT point<dim,number_t>

/**
 * Точка в dim-мерном пространстве
 * @tparam dim размерность пространства
 * @tparam number_t - тип хранимых значений
 */
template<size_t dim, typename number_t>
class point {
private:
    number_t coords[dim];
public:
    point() = default;
    point(const POINT &p);
    explicit point(std::initializer_list<number_t> values);
    ~point();


    template <size_t N, typename num_t>
    friend point<N , num_t> operator-(point<N , num_t> lhs, const point<N , num_t> &rhs);
    template <size_t N, typename num_t>
    friend point<N , num_t> operator*(point<N , num_t> lhs, float a);
    template <size_t N, typename num_t>
    friend point<N , num_t> operator*(float a, point<N , num_t> lhs);
    template <size_t N, typename num_t>
    friend point<N , num_t> operator/(point<N , num_t> lhs, float a);


    bool operator==(const POINT &rhs) const {
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
};

typedef point<3, unsigned char> color;
typedef point<3, float> point3f;
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
        lhs[i] * a;
    }
    return lhs;
}

template<size_t dim, typename number_t>
POINT operator*(float a, POINT rhs) {
    for (size_t i = dim; i--;) {
        rhs[i] * a;
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
        lhs[i] /= a;
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

#endif //GLASSYRENDER_POINT_H
