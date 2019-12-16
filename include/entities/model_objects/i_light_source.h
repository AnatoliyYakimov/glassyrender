//
// Created by Yakimov on 13.10.2019.
//

#ifndef GLASSYRENDER_I_LIGHT_SOURCE_H
#define GLASSYRENDER_I_LIGHT_SOURCE_H

#include "sphere.h"

class i_light_source {
protected:
    float intensity;
    vec3f color = vec3f(1);

    i_light_source() = default;

    explicit i_light_source(float i) : intensity(i) {}
    explicit i_light_source(float i, const vec3f &color) : intensity(i), color(color) {}

public:

    [[nodiscard]] virtual vec3f count_impact(const vec3f &N, const vec3f &p) const = 0;
    [[nodiscard]] virtual vec3f direction( const vec3f &to_point) const = 0;
};

/**
 * Источник света, находящийся в определённой точке мирового пространства.
 */
class point_light_source : public i_light_source {
private:
    vec3f L;
public:
    explicit point_light_source(float i, const vec3f &color, const vec3f &p) : i_light_source(+i, color), L(p) {}

    [[nodiscard]] vec3f count_impact(const vec3f &N, const vec3f &p) const override {
        vec3f LP = (p - L).normalized_copy();
        float norm = LP.norm();
        norm *= norm;
        float LPdotN = LP * N;
        float i = intensity *  LPdotN / norm;
        return i > 0 ? color * i : vec3f{0, 0, 0};
    }

    [[nodiscard]] vec3f direction(const vec3f &to_point) const override {
        return (to_point - L).normalized_copy();
    }
};

/**
 * Бесконечноудалённый от сцены источник света, представляется в виде вектора.
 */
class vector_light_source : public i_light_source {
private:
    vec3f L;
public:
    explicit vector_light_source(float i, const vec3f &color, const vec3f &l) : i_light_source(+i, color), L(
            l.normalized_copy()) {}

    [[nodiscard]] vec3f count_impact(const vec3f &N, const vec3f &p) const override {
        float res = intensity * (L * N);
        return res > 0 ? res * color : vec3f{0, 0, 0};
    }

    [[nodiscard]] vec3f direction(const vec3f &to_point) const override {
        return L;
    }
};

#endif //GLASSYRENDER_I_LIGHT_SOURCE_H
