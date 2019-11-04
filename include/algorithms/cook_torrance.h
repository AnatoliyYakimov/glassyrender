//
// Created by Yakimov on 04.11.2019.
//

#ifndef GLASSYRENDER_COOK_TORRANCE_H
#define GLASSYRENDER_COOK_TORRANCE_H

#include "../entities/algebra/vec.h"
#include "brdf.h"

class schlicks_approximation : public frensel_equation {
public:
    vec3f F(const float &VdotH, const vec3f &F0) override {
        float p = std::pow(1 - VdotH, 5.0);
        return F0 + (vec3f{1, 1, 1} - F0) * p;
    }

    vec3f operator()(const float &VdotH, const vec3f &F0) override {
        return F(VdotH, F0);
    }
};

class SchlickGGX : public geometry_attenuation {
public:
    float G(const float &NdotV, const float &NdotL, const float &roughness) override {
        return Ginternal(NdotV, roughness) * Ginternal(NdotL, roughness);
    }

    float operator()(const float &NdotV, const float &NdotL, const float &roughness) override {
        return G(NdotV, NdotL, roughness);
    }

private:
    float Ginternal(const float &NdotX, const float &roughness) {
        float divider = NdotX * (1.0 - roughness) + roughness;
        return NdotX / divider;
    }
};

class GGX_distribution : public normal_distribution {
public:
    float D(const float &NdotH, float roughness) override {
        float a = roughness * roughness;
        float divider = (a - 1) * NdotH * NdotH + 1;
        return a / (divider * divider);
    }

    float operator()(const float &NdotH, const float &roughness) override {
        return D(NdotH, roughness);
    }
};

#endif //GLASSYRENDER_COOK_TORRANCE_H
