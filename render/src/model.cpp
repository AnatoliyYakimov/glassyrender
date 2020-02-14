//
// Created by Yakimov on 30.09.2019.
//

#include <algorithm>
#include "../include/model.h"


intersection *
    model::nearest_collision(const vec3f &fromPoint, const vec3f &V, float t_min, float t_max) const {
    std::vector<intersection> intersections;
    for (const auto object : objects) {
        intersection *is = object->ray_intersection(fromPoint, V, t_min, t_max);
        if (is == nullptr) {
            continue;
        }
        intersections.emplace_back(is);
    }
    if (intersections.empty()) {
        return nullptr;
    }
    const intersection *nearest = intersections.begin().base();
    float d_min = nearest->distance;
    for (const auto &item : intersections) {
        float d = item.distance;
        if (d < d_min) {
            nearest = &item;
            d_min = d;
        }
    }
    return new intersection(*nearest);
}

bool model::any_collision(const vec3f &fromPoint, const vec3f &V, float t_min, float t_max) const {
    for (const auto sphere : objects) {
        intersection*p = sphere->ray_intersection(fromPoint, V, t_min, t_max);
        if (p != nullptr) {
            delete p;
            return true;
        }
    }
    return false;
}

