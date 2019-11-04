//
// Created by Yakimov on 01.11.2019.
//

#include "../../include/algorithms/brdf.h"

vec3f
BRDF::count_irradiance(const vec3f &p, const vec3f &v, const vec3f &n, const material &material, const model &model) {
    vec3f l;
    vec3f irradiance = {0, 0, 0};
    vec3f Fdiffuse = material.albedo;
    float k = (material.Kd + 1) * (material.Kd + 1) / 8;
    float NdotH, NdotL, NdotV, VdotH;
    float _G, _D;
    vec3f _F;
    for (const auto *light : model.lights) {
        l = light->direction(p);
        if (model.any_collision(p, -l, eps, inf)) {
            continue;
        }
        vec3f h = (l + v).normalize();
        NdotL = std::max(n * l, 0.0f);
        NdotV = std::max(n * v, 0.0f);
        NdotH = std::max(n * h, 0.0f);
        VdotH = std::max(v * h, 0.0f);
        float divider = 4 * NdotL * NdotV;
        _G = G(NdotV, NdotL, k);
        _D = D(NdotH, material.Kd);
        _F = F(VdotH, material.frenel);
        vec3f Fcook_torrance = _G * _F * _D / divider;
        vec3f L = light->count_impact(n, p);
        irradiance = irradiance +
                     ((material.Kd * Fdiffuse + Fcook_torrance)).mix(L);
    }
    return irradiance / M_PI;
}
