//
// Created by Yakimov on 05.10.2019.
//

#ifndef GLASSYRENDER_POINT_H
#define GLASSYRENDER_POINT_H

#include <windef.h>
#include <wingdi.h>
#include <ostream>


/**
 * Точка в dim-мерном пространстве
 * @tparam dim размерность пространства
 * @tparam number_t - тип хранимых значений
 */
template<size_t dim, typename number_t>
class point {
public:
    number_t coords[dim];
    point() = default;
    point(const point<dim,number_t> &p);
    point(std::initializer_list<number_t> values);
    ~point();

    point<dim + 1, number_t> extend() const;
    point<dim - 1, number_t> shrink() const;

    template <size_t N, typename num_t>
    friend point<N , num_t> operator-(point<N , num_t> lhs, const point<N , num_t> &rhs);
    template <size_t N, typename num_t>
    friend point<N , num_t> operator*(point<N , num_t> lhs, float a);
    template <size_t N, typename num_t>
    friend point<N , num_t> operator*(float a, point<N , num_t> lhs);
    template <size_t N, typename num_t>
    friend point<N , num_t> operator/(point<N , num_t> lhs, float a);

    friend inline COLORREF get_color_ref(const point<3, BYTE> &col);


    bool operator==(const point<dim,number_t> &rhs) const {
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

    template<size_t N, typename num>
    friend std::ostream &operator<<(std::ostream &os, const point &point);
};

typedef point<3, BYTE> color;
typedef point<3, float> point3f;

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
point<dim,number_t>::point(const point<dim,number_t> &p) {
    for (size_t i = dim; i--;) {
        this->coords[i] = p[i];
    }
}

template<size_t dim, typename number_t>
point<dim, number_t>::~point() {
}

template<size_t dim, typename number_t>
point<dim,number_t> operator*(point<dim,number_t> lhs, float a) {
    for (size_t i = dim; i--;) {
        lhs[i] = static_cast<number_t>(lhs[i] * a);
    }
    return lhs;
}

template<size_t dim, typename number_t>
point<dim,number_t> operator*(float a, point<dim,number_t> rhs) {
    for (size_t i = dim; i--;) {
        rhs[i] = static_cast<number_t>(rhs[i] * a);
    }
    return rhs;
}

template<size_t dim, typename number_t>
point<dim,number_t> operator+(point<dim,number_t> lhs, const point<dim,number_t> &rhs) {
    for (size_t i = dim; i--;) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<size_t dim, typename number_t>
point<dim,number_t> operator-(point<dim,number_t> lhs, const point<dim,number_t> &rhs) {
    for (size_t i = dim; i--;) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}

template<size_t dim, typename number_t>
point<dim,number_t> operator/(point<dim,number_t> lhs, const float a) {
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

inline COLORREF get_color_ref(const point<3, BYTE>& col) {
    return RGB(col[0], col[1], col[2]);
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

#endif //GLASSYRENDER_POINT_H
