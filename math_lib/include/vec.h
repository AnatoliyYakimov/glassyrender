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

typedef std::vector<vec3f> vec3f_arr;


template<size_t dim, typename number_t>
inline COLORREF vec<dim,number_t>::get_color_ref() {
    return RGB(255 * (*this)[0], 255 * (*this)[1], 255 * (*this)[2]);
}

template<size_t dim, typename number_t>
vec<dim,number_t>::vec(const vec<dim,number_t> &v) : vec() {
    for (size_t i = dim; i--;) {
        (*this)[i] = v[i];
    }
}
template<size_t dim, typename number_t>
vec<dim, number_t>::vec(const float &val) : vec() {
    for (size_t i = dim; i--;) {
        (*this)[i] = val;
    }
}

template<size_t dim, typename number_t>
float vec<dim,number_t>::norm() const {
    float sum = 0;
    for (size_t i = dim; i--;) {
        sum += (*this)[i] * (*this)[i];
    }
    return (std::sqrt(sum));
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
vec<dim,number_t> vec<dim,number_t>::normalized_copy() const {
    return (*this) / this->norm();
}

template<size_t dim, typename number_t>
vec<dim,number_t>::vec(std::initializer_list<number_t> &&values) : vec() {
    assert(values.size() == dim);
    auto it = values.end();
    for (size_t i = dim; i--;) {
        (*this)[i] = *(--it);
    }
}

template<size_t dim, typename number_t>
vec<dim - 1, number_t> vec<dim,number_t>::shrink() const {
    vec<dim - 1, number_t> res;
    const number_t last = (*this)[dim - 1];
    for (size_t i = dim - 1; i--;) {
        res[i] = (*this)[i];
    }
    return res;
}

template<size_t dim, typename number_t>
vec<dim + 1, number_t> vec<dim,number_t>::extend(number_t value) const {
    vec<dim + 1, number_t> res;
    for (size_t i = dim; i--;) {
        res[i] = (*this)[i];
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
        v[i] *= (*this)[i];
    }
    return v;
}

template<size_t dim, typename number_t>
vec<dim, number_t> &vec<dim, number_t>::normalize(){
    float norm = this->norm();
    for (size_t i = dim; i--;) {
        coords[i] /= norm;
    }
    return *this;
}

#endif //GLASSYRENDER_vec<dim,number_t>_H
