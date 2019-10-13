//
// Created by Yakimov on 13.10.2019.
//

#ifndef GLASSYRENDER_I_LIGHT_SOURCE_H
#define GLASSYRENDER_I_LIGHT_SOURCE_H

#include "sphere.h"

class i_light_source {
protected:
    float intensity;
    i_light_source() = default;
    explicit i_light_source(float i) : intensity(i) {}

public:
    virtual float count_impact(const sphere& S, const point3f &p) const = 0;
};

/**
 * Базовый свет окружения, безусловно влияет на каждую точку в пространстве
 */
class ambient_light_source : public i_light_source {
public:
    ambient_light_source() = default;
    explicit ambient_light_source(float i) : i_light_source(i) {}

    float count_impact(const sphere &S, const point3f &p) const  override {
        return intensity;
    }

};

/**
 * Источник света, находящийся в определённой точке мирового пространства.
 */
class point_light_source : public i_light_source {
private:
    point3f L;
public:
    explicit point_light_source(float i, const point3f &p) : i_light_source(i), L(p) {}

    float count_impact(const sphere &S, const point3f &p) const  override {
        vec3f LP = vec3f{L, p}.normalize();
        vec3f N = S.norm(p);
        return intensity * LP * N;
    }
};

/**
 * Бесконечноудалённый от сцены источник света, представляется в виде вектора.
 */
class vector_line_source : public i_light_source {
private:
    vec3f L;
public:
    explicit vector_line_source(float i, const vec3f &l) : i_light_source(i), L(l) {}

    float count_impact(const sphere &S, const point3f &p) const override {
        return intensity * L * S.norm(p);
    }
};

#endif //GLASSYRENDER_I_LIGHT_SOURCE_H
