//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_MODEL_H
#define GLASSYRENDER_MODEL_H

#include <vector>
#include "sphere.h"
#include "../../Constants.h"
#include "i_light_source.h"

class model {
public:
    std::vector<i_object *> objects;
    std::vector<i_light_source *> lights;
    vec3f scene_color = vec3f(1);

    model() = default;

    intersection* nearest_collision(
            const vec3f &fromPoint, const vec3f &V,
            float t_min, float t_max) const;
    bool any_collision(const vec3f &fromPoint, const vec3f &V,
                       float t_min, float t_max) const;
};


#endif //GLASSYRENDER_MODEL_H