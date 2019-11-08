//
// Created by Yakimov on 16.10.2019.
//

#ifndef GLASSYRENDER_OBJECTS_H
#define GLASSYRENDER_OBJECTS_H

#include <vector>
#include "../algebra/affine_transform.h"
#include "material.h"

struct texture {
    material material;
    vec3f n;
    vec3f p;
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
    [[nodiscard]] virtual vec3f* ray_intersection(const vec3f &from_point, const vec3f &v, const float& t_min, const float& t_max) const = 0;
};


#endif //GLASSYRENDER_OBJECTS_H
