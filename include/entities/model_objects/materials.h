//
// Created by Yakimov on 01.11.2019.
//

#ifndef GLASSYRENDER_MATERIALS_H
#define GLASSYRENDER_MATERIALS_H

#include <memory>
#include "../algebra/vec.h"
#include "../textures/i_texture.h"

class material_snapshot {
public:
    vec3f albedo;
    vec3f frenel;
    float Ks;
    float Kd;

    material_snapshot() = default;

    material_snapshot(const material_snapshot &m) : albedo(m.albedo), frenel(m.frenel), Ks(m.Ks), Kd(m.Kd) {};

    material_snapshot(const vec3f &albedo, const vec3f &frenel, float ks)
            : albedo(albedo),
              Ks(ks),
              Kd(1.0f - ks),
              frenel(frenel) {};

    material_snapshot(const vec3f &albedo, float ks)
            : material_snapshot(albedo, ks * vec3f(0.4).mix(albedo), ks) {};
};

class i_material {
public:
    virtual material_snapshot material_at_point(const vec2f &p) = 0;
};

class uniform_material : public i_material {
private:
    material_snapshot mat;
public:
    uniform_material() = default;
    uniform_material(const material_snapshot &mat) : mat(mat) {}

    material_snapshot material_at_point(const vec2f &p) override {
        return mat;
    }
};

class textured_material : public i_material {
protected:
    std::shared_ptr<i_texture> albedo;
    std::shared_ptr<i_texture> specular;
public:
    textured_material() = default;

    textured_material(i_texture *albedo, i_texture *specular)
                      : albedo(albedo), specular(specular) {}

    material_snapshot material_at_point(const vec2f &p) override {
        return material_snapshot(albedo->texture_at_point(p), specular->texture_at_point(p)[0]);
    }
};

#endif //GLASSYRENDER_MATERIALS_H
