//
// Created by Yakimov on 25.10.2019.
//
#ifndef GLASSYRENDER_VECTOR_UTILS_H
#include "../../include/entities/vector_utils.h"
#endif

template<typename number_t>
vec<3, number_t> vector_utils<number_t>::vector_product(const vec<3, number_t> &v1, const vec<3, number_t> &v2) {
    vec<3, number_t> res;
    matrix<3, 3, number_t> mat = {
            vec3f(0),
            v1,
            v2
    };
    auto min1 = mat.get_minor(0, 0);
    auto min2 = mat.get_minor(0, 1);
    auto min3 = mat.get_minor(0, 2);
    res[0] = min1.determinant();
    res[1] = - min2.determinant();
    res[2] = min3.determinant();
    return res;
}

