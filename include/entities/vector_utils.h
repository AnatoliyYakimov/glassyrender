//
// Created by Yakimov on 24.10.2019.
//

#ifndef GLASSYRENDER_VECTOR_UTILS_H
#define GLASSYRENDER_VECTOR_UTILS_H

#include "matrix.h"

template<typename number_t>
class vector_utils {
public:
    static vec<3, number_t> vector_product(const vec<3, number_t> &v1, const vec<3, number_t> &v2);
};


#include "../../sources/entities/vector_utils.cpp"

#endif //GLASSYRENDER_VECTOR_UTILS_H
