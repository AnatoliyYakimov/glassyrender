//
// Created by Yakimov on 05.10.2019.
//

#ifndef GLASSYRENDER_SPHERE_H
#define GLASSYRENDER_SPHERE_H

#include <utility>
#include "vec.h"

class sphere {
public:
    float R;
    vec3f O;
    vec3f col;

    [[nodiscard]] std::pair<float, float> ray_collision(const vec3f &fromPoint, const vec3f &D) const {
        vec3f OC = fromPoint - O;
        float k1 = 2 * (D * D);
        float k2 = 2 * (D * OC);
        float k3 = (OC * OC) - R * R;
        float d = k2 * k2 - 2 * k1 * k3;
        if (d < 0) {
            return std::make_pair(-1, -1);
        }
        float sqrt = std::sqrt(d);
        float x1 = (sqrt - k2) / (k1);
        float x2 = (-sqrt - k2) / (k1);
        return std::pair{x1, x2};
    }

    vec3f norm(const vec3f &p) const {
        return (O - p).normalize();
    }
};

#endif //GLASSYRENDER_SPHERE_H
