//
// Created by Yakimov on 30.09.2019.
//

#include <algorithm>
#include "../../include/scene/model.h"


std::pair<vec3f, const sphere *> *
model::nearest_collision(const vec3f &fromPoint, const vec3f &V, float t_min, float t_max) {
    std::vector<std::pair<float, const sphere &>> points;
    for (const auto &sphere : spheres) {
        auto[t1, t2] = sphere.ray_collision(fromPoint, V);
        bool b1 = t1 > t_min && t1 < t_max,
                b2 = t2 > t_min && t2 < t_max;
        if (b1 || b2) {
            float min = 0;
            if (b1 && b2) {
                min = t1 < t2 ? t1 : t2;
            } else {
                min = b1 ? t1 : t2;
            }
            points.emplace_back(min, sphere);
        }
    }
    if (points.empty()) {
        return nullptr;
    }
    const std::pair<float, const sphere &> *nearest = points.begin().base();
    for (const auto &item : points) {
        if (item.first < nearest->first) {
            nearest = &item;
        }
    }
    const vec3f &p = fromPoint + (nearest->first * V);
    const sphere &s = nearest->second;
    return new std::pair<vec3f, const sphere *>(p, &s);
}

bool model::any_collision(const vec3f &fromPoint, const vec3f &V, float t_min, float t_max) {
    for (const auto &sphere : spheres) {
        auto[t1, t2] = sphere.ray_collision(fromPoint, V);
        bool b1 = t1 > t_min && t1 < t_max,
                b2 = t2 > t_min && t2 < t_max;
        if (b1 || b2) {
            return true;
        }
    }
    return false;
}

