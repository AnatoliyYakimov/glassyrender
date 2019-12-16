//
// Created by Yakimov on 10.10.2019.
//

#ifndef GLASSYRENDER_vec_H
#define GLASSYRENDER_vec_H

#include <ostream>
#include <cmath>
#include <cassert>
#include <windef.h>

/**
 * Класс, реализующий функционал вектора линейной алгебры.
 * @tparam dim - размерность ветора
 * @tparam number_t - тип хранимого значения
 */
template<size_t dim, typename number_t>
class vec {
private:
    number_t coords[dim];

public:

    vec() = default;

    vec(const vec &v);

    explicit vec(const float &val);

    vec(std::initializer_list<number_t> &&values);

    ~vec(){};

    [[nodiscard]] float norm() const;

    [[nodiscard]] vec<dim,number_t> normalized_copy() const;

    vec<dim,number_t>& normalize();

    [[nodiscard]] vec<dim,number_t> mix(vec<dim,number_t> v) const;

    vec<dim + 1, number_t> extend(number_t value) const;

    vec<dim - 1, number_t> shrink() const;

    inline COLORREF get_color_ref();

    vec<dim, number_t> pow(float a) const;

    template<size_t N, typename num_t>
    friend vec<N, num_t> exp(vec<N, num_t> v);

    vec<dim, number_t> &operator=(const vec<dim, number_t> &v) {
        for (size_t i = dim; i--;) {
            (*this)[i] = v[i];
        }
        return *this;
    }

    vec<dim, number_t> &operator+=(const vec<dim, number_t> &v) {
        for (size_t i = dim; i--;) {
            (*this)[i] += v[i];
        }
        return *this;
    }

    vec<dim, number_t> &operator-=(const vec<dim, number_t> &v) {
        for (size_t i = dim; i--;) {
            (*this)[i] += v[i];
        }
        return *this;
    }

    vec<dim, number_t> &operator*=(const vec<dim, number_t> &v) {
        for (size_t i = dim; i--;) {
            (*this)[i] *= v[i];
        }
        return *this;
    }

    /**
     * Скалярное произведение векторов.
     * @tparam N - размерность
     * @tparam num_t - тип хранимых значений
     * @param v1 - вектор
     * @param v2 - вектор
     * @return - скалярное произведение векторов
     */
    template<size_t N, typename num_t>
    friend float operator*(const vec<dim,number_t> &v1, const vec<dim,number_t> &v2);

    template<size_t N, typename num_t>
    friend vec<dim,number_t> operator+(vec<dim,number_t> lhs, const vec<dim,number_t> &rhs);

    template<size_t N, typename num_t>
    friend vec<dim,number_t> operator+(float a, vec<dim,number_t> rhs);

    template<size_t N, typename num_t>
    friend vec<dim,number_t> operator-(vec<dim,number_t> lhs, const vec<dim,number_t> &rhs);

    template<size_t N, typename num_t>
    friend vec<dim,number_t> operator*(vec<dim,number_t> lhs, float a);

    template<size_t N, typename num_t>
    friend vec<dim,number_t> operator*(float a, vec<dim,number_t> lhs);

    template<size_t N, typename num_t>
    friend vec<dim,number_t> operator/(vec<dim,number_t> lhs, float a);

    template<size_t N, typename num_t>
    friend vec<dim,number_t> operator/(vec<dim,number_t> lhs, const vec<dim,number_t>& rhs);

    bool operator==(const vec<dim,number_t> &rhs) const {
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



typedef vec<4, float> vec4f;
typedef vec<3, float> vec3f;
typedef vec<2, float> vec2f;

typedef vec<3, int> vec3i;
typedef vec<2, int> vec2i;


#include "../../../sources/entities/algebra/vec.cpp"

#endif //GLASSYRENDER_vec<dim,number_t>_H
