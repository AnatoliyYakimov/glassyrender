//
// Created by Yakimov on 13.10.2019.
//

#ifndef GLASSYRENDER_LIGHT_H
#define GLASSYRENDER_LIGHT_H

#include "sphere.h"

class light {
protected:
    float intensity;
    vec3f color = vec3f(1);

    light() = default;

    explicit light(float i) : intensity(i) {}
    explicit light(float i, const vec3f &color) : intensity(i), color(color) {}

public:

    [[nodiscard]] virtual vec3f count_impact(const vec3f &N, const vec3f &p) const = 0;
    [[nodiscard]] virtual vec3f direction( const vec3f &to_point) const = 0;
};

/**
 * Источник света, находящийся в определённой точке мирового пространства.
 */
class point_light_source : public light {
private:
    vec3f L;
public:
    explicit point_light_source(float i, const vec3f &color, const vec3f &p) : light(+i, color), L(p) {}

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
class vector_light_source : public light {
private:
    vec3f L;
public:
    explicit vector_light_source(float i, const vec3f &color, const vec3f &l) : light(+i, color), L(
            l.normalized_copy()) {}

    [[nodiscard]] vec3f count_impact(const vec3f &N, const vec3f &p) const override {
        float res = intensity * (L * N);
        return res > 0 ? res * color : vec3f{0, 0, 0};
    }

    [[nodiscard]] vec3f direction(const vec3f &to_point) const override {
        return L;
    }
};

typedef std::shared_ptr<light> light_sp;
#endif //GLASSYRENDER_LIGHT_H
