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
    /**
     * Высчитывает влияние светового источника на точку в пространстве. Метод НЕ должен возвращать отрицательные значения
     * @param S
     * @param p
     * @return
     */
    virtual float count_impact(const vec3f &N, const vec3f &p) const = 0;
    virtual vec3f direction( const vec3f &to_point) const = 0;
};

/**
 * Источник света, находящийся в определённой точке мирового пространства.
 */
class point_light_source : public i_light_source {
private:
    vec3f L;
public:
    explicit point_light_source(float i, const vec3f &p) : i_light_source(i), L(p) {}

    float count_impact(const vec3f &N, const vec3f &p) const override {
        vec3f LP = p - L;
        float norm = LP.norm();
        norm *= norm;
        float res = intensity * LP * N / norm;
        return res > 0 ? res : 0;
    }

    vec3f direction(const vec3f &to_point) const override {
        return L - to_point;
    }
};

/**
 * Бесконечноудалённый от сцены источник света, представляется в виде вектора.
 */
class vector_light_source : public i_light_source {
private:
    vec3f L;
public:
    explicit vector_light_source(float i, const vec3f &l) : i_light_source(i), L(l.normalize()) {}

    float count_impact(const vec3f &N, const vec3f &p) const override {
        float res = intensity * (L * N);
        return res > 0 ? res : 0;
    }

    vec3f direction( const vec3f &to_point) const override {
        return L;
    }
};

#endif //GLASSYRENDER_I_LIGHT_SOURCE_H
