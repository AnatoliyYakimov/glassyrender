//
// Created by Yakimov on 16.10.2019.
//

#ifndef GLASSYRENDER_I_OBJECT_H
#define GLASSYRENDER_I_OBJECT_H

#include <vector>
#include "../algebra/affine_transform.h"
#include "material.h"


class intersection {
public:
    vec3f intersection_point;
    float distance;
    vec3f normal;
    material mat;

    intersection() : intersection_point(), distance(), normal(), mat() {}

    intersection(const intersection &is) : intersection_point(is.intersection_point), distance(is.distance),
                                           normal(is.normal), mat(is.mat) {}

    intersection(const intersection *is) : intersection(*is) {}

    intersection(const vec3f &intersectionPoint, float distance, const vec3f &normal, const material &mat)
            : intersection_point(intersectionPoint), distance(distance), normal(normal), mat(mat) {}
};

class i_object {
protected:
    affine_transform to_local;
    affine_transform to_world;

public:
    i_object() : to_local(affine_transform::identity()), to_world(affine_transform::identity()) {};

    i_object(const i_object &o) = default;

    /**
     * Высчитывает пересечение с объектом
     * @param from_point - точка из которой выходит луч
     * @param v - направление луча
     * @return - локальные координаты пересечения
     */
    [[nodiscard]] virtual intersection *
    ray_intersection(const vec3f &from_point, const vec3f &v, const float &t_min, const float &t_max) const = 0;
};


#endif //GLASSYRENDER_I_OBJECT_H
