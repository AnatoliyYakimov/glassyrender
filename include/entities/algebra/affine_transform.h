//
// Created by Yakimov on 18.10.2019.
//

#ifndef GLASSYRENDER_AFFINE_TRANSFORM_H
#define GLASSYRENDER_AFFINE_TRANSFORM_H

#include "matrix.h"
#include <cmath>

typedef matrix<4, 4, float> affine_transform;

class affine_transform_factory {
public:
    static affine_transform move(const vec3f &p);

    static affine_transform to_point(const vec3f &from, const vec3f &to);

    static affine_transform rotate(float phi, const vec3f &axis_p, const vec3f &axis_v);

    static affine_transform rotateX(float phi, const vec3f &p);

    static affine_transform rotateY(float phi, const vec3f &p);

    static affine_transform rotateZ(float phi, const vec3f &p);

    static affine_transform stretch(const vec3f &p);

    static affine_transform to_coords_center(const vec3f &p);

private:
    static float inline to_radians(float degrees) {
        return degrees * M_PI / 180;
    }
};


#endif //GLASSYRENDER_AFFINE_TRANSFORM_H
