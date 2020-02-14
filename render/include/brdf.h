//
// Created by Yakimov on 01.11.2019.
//

#ifndef GLASSYRENDER_BRDF_H
#define GLASSYRENDER_BRDF_H

#include <functional>
#include <vec.h>
#include "sphere.h"
#include "model.h"

class geometry_attenuation {
public:
    virtual float G(const float &NdotV, const float &NdotL, const float &roughness) = 0;
    virtual float operator()(const float &NdotV, const float &NdotL, const float &roughness) = 0;
};

class normal_distribution {
public:
    virtual float D(const float &NdotH, float roughness) = 0;
    virtual float operator()(const float &NdotH, const float &roughness) = 0;

};

class frensel_equation {
public:
    virtual vec3f F(const float &VdotH, const vec3f &F0) = 0;
    virtual vec3f operator()(const float &VdotH, const vec3f &F0) = 0;

};

class BRDF {
public:

    normal_distribution &D;
    geometry_attenuation &G;
    frensel_equation &F;

    BRDF(normal_distribution* d, geometry_attenuation* g, frensel_equation* f) : D(*d), G(*g), F(*f) {};
    /**
     *
     * @param p - точка пересечеия
     * @param v - направление наблюдателя
     * @param n - нормаль к поверхности
     * @param material - материл поверхности
     * @param model - модель которую необходимо рендерить
     * @return - цвет поврхности
     */
    vec3f count_irradiance(const vec3f &p,
                           const vec3f &v,
                           const vec3f &n,
                           const vec3f &albedo,
                           const vec3f &frenel,
                           float roughness,
                           float ao,
                           const model &model);
};


#endif //GLASSYRENDER_BRDF_H
