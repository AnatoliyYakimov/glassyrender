//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_MODEL_H
#define GLASSYRENDER_MODEL_H

#include <vector>
#include "../entities/sphere.h"
#include "../../Constants.h"
#include "../entities/i_light_source.h"

class model {
public:
    std::vector<sphere> spheres;
    std::vector<i_light_source *> lights;
    vec3f scene_color = {1, 1, 1};

    model() = default;

    std::pair<vec3f, const sphere *> *nearest_collision(
            const vec3f &fromPoint, const vec3f &V,
            float t_min, float t_max);
    bool any_collision(const vec3f &fromPoint, const vec3f &V,
                       float t_min, float t_max);
};


#endif //GLASSYRENDER_MODEL_H
