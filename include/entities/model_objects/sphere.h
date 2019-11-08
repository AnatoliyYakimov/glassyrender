//
// Created by Yakimov on 05.10.2019.
//

#ifndef GLASSYRENDER_SPHERE_H
#define GLASSYRENDER_SPHERE_H

#include <utility>
#include "../algebra/vec.h"
#include "material.h"
#include "objects.h"

class sphere : public i_object{
public:
    float R;
    vec3f O;
    material mat;

    sphere(float r, const vec3f &o, const material &material) : R(r), O(o), mat(material) {}
    sphere(const sphere &s) = default;

    [[nodiscard]] vec3f* ray_intersection(const vec3f &from_point, const vec3f &v, const float& t_min, const float& t_max) const override {
        vec3f OC = from_point - O;
        float k1 = 2 * (v * v);
        float k2 = 2 * (v * OC);
        float k3 = (OC * OC) - R * R;
        float d = k2 * k2 - 2 * k1 * k3;
        if (d < 0) {
            return nullptr;
        }
        float sqrt = std::sqrt(d);
        float t1 = (sqrt - k2) / (k1);
        float t2 = (-sqrt - k2) / (k1);
        bool b1 = t1 > t_min && t1 < t_max,
                b2 = t2 > t_min && t2 < t_max;
        if (b1 || b2) {
            float min = 0;
            if (b1 && b2) {
                min = t1 < t2 ? t1 : t2;
            } else {
                min = b1 ? t1 : t2;
            }
            return new vec3f(min * v);
        }
        else {
            return nullptr;
        }
    }


    vec3f normal_at_point(const vec3f &p) const {
        return (O - p).normalize();
    }
};

#endif //GLASSYRENDER_SPHERE_H
