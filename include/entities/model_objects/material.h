//
// Created by Yakimov on 01.11.2019.
//

#ifndef GLASSYRENDER_MATERIAL_H
#define GLASSYRENDER_MATERIAL_H

#include "../algebra/vec.h"

class material {
public:
    vec3f albedo;
    vec3f frenel;
    float Ks;
    float Kd;

    material() = default;

    material(const material &m) : albedo(m.albedo), frenel(m.frenel), Ks(m.Ks), Kd(m.Kd) {};

    material(const vec3f &albedo, const vec3f& frenel, float ks)
            : albedo(albedo),
              Ks(ks),
              Kd(1.0f - ks),
              frenel(frenel) {};

    material(const vec3f &albedo, float ks)
            : material(albedo, ks * vec3f(0.4).mix(albedo), ks){};
};

#endif //GLASSYRENDER_MATERIAL_H
