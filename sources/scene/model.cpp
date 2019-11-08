//
// Created by Yakimov on 30.09.2019.
//

#include <algorithm>
#include <memory>
#include "../../include/scene/model.h"


std::pair<vec3f, const sphere *> *
model::nearest_collision(const vec3f &fromPoint, const vec3f &V, float t_min, float t_max) const {
    std::vector<std::pair<const vec3f* ,const sphere &>> points;
    for (const auto &sphere : spheres) {
        vec3f* p = sphere.ray_intersection(fromPoint, V, t_min, t_max);
        if (p == nullptr){
            continue;
        }
            points.emplace_back(std::make_pair(p, sphere));
    }
    if (points.empty()) {
        return nullptr;
    }
    const std::pair<const vec3f* ,const sphere &> *nearest = points.begin().base();
    float d_min = nearest->first->norm();
    for (const auto &item : points) {
        float d = item.first->norm();
        if (d < d_min) {
            nearest = &item;
            d_min = d;
        }
    }
    const sphere &s = nearest->second;
    return new std::pair<vec3f, const sphere *>(vec3f(fromPoint + *nearest->first), &s);
}

bool model::any_collision(const vec3f &fromPoint, const vec3f &V, float t_min, float t_max) const {
    for (const auto &sphere : spheres) {
        vec3f* p = sphere.ray_intersection(fromPoint, V, t_min, t_max);
        if (p != nullptr) {
            delete p;
            return true;
        }
    }
    return false;
}

