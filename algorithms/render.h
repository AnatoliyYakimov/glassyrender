//
// Created by Yakimov on 14.10.2019.
//

#ifndef GLASSYRENDER_RENDER_H
#define GLASSYRENDER_RENDER_H

#include <utility>
#include <vector>
#include "../Entities/sphere.h"

inline std::pair<const sphere *, const point3f *> *nearest_collision(
        const std::vector<sphere> &spheres, const point3f &fromPoint, const vec3f &V,
        float t_min, float t_max) {
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
    const point3f &p = fromPoint + (nearest->first * V).to_point();
    const sphere &s = nearest->second;
    return new std::pair<const sphere *, const point3f *>(&s, &p);
}

#endif //GLASSYRENDER_RENDER_H
