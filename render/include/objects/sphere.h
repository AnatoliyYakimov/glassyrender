//
// Created by Yakimov on 05.10.2019.
//

#ifndef GLASSYRENDER_SPHERE_H
#define GLASSYRENDER_SPHERE_H

#include <utility>
#include <memory>
#include <vec.h>
#include <objects/i_object.h>

class sphere : public i_object {
protected:
    const vec3f O = vec3f{0, 0, 0};
    float R;


public:

    sphere(float r,
           const material_sp &_mat)
            : i_object(_mat),
              R(r) {}

    sphere(const sphere &s) = default;

    [[nodiscard]] intersection *ray_intersection(const vec3f &from_point,
                                                 const vec3f &dir,
                                                 const float &t_min,
                                                 const float &t_max) const override {
        vec3f OC = from_point - to_world * O;
        float k1 = 2 * (dir * dir);
        float k2 = 2 * (dir * OC);
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
            vec3f p_world = from_point + min * dir;
            vec3f p_local = to_local * p_world;
            vec3f p_n = p_local.normalized_copy();
            float x_t = 0.5 + atan2(p_n[0], p_n[2]) / (2 * M_PI);
            float y_t = 0.5 - asin(p_n[1]) / M_PI;
            vec2f p_texture = vec2f{x_t, y_t};
            vec3f normal = (to_world * O - p_world).normalize();
            vec2f vt = vec2f{x_t, y_t};
            intersection *is =
                    new intersection(p_world,
                                     normal,
                                     vt,
                                     min);
            return is;
        } else {
            return nullptr;
        }
    }

};

#endif //GLASSYRENDER_SPHERE_H
