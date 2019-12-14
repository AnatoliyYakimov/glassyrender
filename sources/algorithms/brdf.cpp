//
// Created by Yakimov on 01.11.2019.
//

#include "../../include/algorithms/brdf.h"

vec3f
BRDF::count_irradiance(const vec3f &p,
                       const vec3f &v,
                       const vec3f &n,
                       const vec3f &albedo,
                       const vec3f &frenel,
                       float roughness,
                       float ao,
                       const model &model) {
    vec3f l;
    vec3f irradiance = vec3f(0);
    vec3f Fdiffuse = albedo;
    float k = (roughness + 1) * (roughness + 1) / 8;
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
        float divider = 4 * NdotL * NdotV + std::numeric_limits<float>::min();
        _G = G(NdotV, NdotL, k);
        _D = D(NdotH, roughness);
        _F = F(VdotH, frenel);
        vec3f Fcook_torrance = _G * _F * _D / divider;
        vec3f L = light->count_impact(n, p);
        irradiance = irradiance +
                (roughness * Fdiffuse + Fcook_torrance).mix(L);
    }
    return irradiance * ao / M_PI;
}
