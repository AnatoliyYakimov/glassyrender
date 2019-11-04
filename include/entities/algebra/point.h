//
// Created by Yakimov on 05.10.2019.
//

#ifndef GLASSYRENDER_POINT_H
#define GLASSYRENDER_POINT_H

#include <windef.h>
#include <wingdi.h>
#include <ostream>
#define POINT point<dim,number_t>

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
    point(const POINT &p);
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

    template<size_t N, typename num>
    friend std::ostream &operator<<(std::ostream &os, const point &point);
};

typedef point<3, BYTE> color;
typedef point<3, float> point3f;

#include "../../../sources/entities/algebra/point.cpp"
#endif //GLASSYRENDER_POINT_H
