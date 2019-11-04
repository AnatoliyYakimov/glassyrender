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

    material(const material &m) = default;

    material(const vec3f &albedo, const vec3f& frenel, float ks)
            : albedo(albedo),
              Ks(ks),
              Kd(1.0f - ks),
              frenel(frenel) {};
};

#endif //GLASSYRENDER_MATERIAL_H
