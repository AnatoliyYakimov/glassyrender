//
// Created by Yakimov on 16.10.2019.
//

#ifndef GLASSYRENDER_I_OBJECT_H
#define GLASSYRENDER_I_OBJECT_H

#include <vector>
#include <affine_transform.h>
#include "i_rgb_texture.h"
#include "i_monochrome_texture.h"


class intersection {
public:
    vec3f intersection_point;
    float distance;
    vec3f normal;
    vec3f albedo;
    float roughness;
    float ao;
    float metalness;
    vec3f frenel;

    intersection(const vec3f &intersection_point,
                 float distance,
                 const vec3f &normal,
                 const vec3f &albedo,
                 float roughness,
                 float ao)
            : intersection_point(intersection_point),
              distance(distance),
              normal(normal),
              albedo(albedo),
              roughness(roughness),
              metalness(1.0f - roughness),
              frenel(metalness * albedo * 0.4),
              ao(ao) {}

    intersection(const intersection &is) :
            intersection_point(is.intersection_point),
            distance(is.distance),
            normal(is.normal),
            albedo(is.albedo),
            roughness(is.roughness),
            metalness(is.roughness),
            frenel(is.frenel),
            ao(is.ao) {}

    intersection(const intersection *is) : intersection(*is) {}

};

class i_object {
protected:
    affine_transform to_local;
    affine_transform to_world;
public:

    std::shared_ptr<i_rgb_texture> albedo_map;
    std::shared_ptr<i_monochrome_texture> roughness_map;
    std::shared_ptr<i_monochrome_texture> ao_map;
    std::shared_ptr<i_rgb_texture> normal_map;

    i_object()
            : to_local(affine_transform::identity()),
              to_world(affine_transform::identity()) {};

    i_object(i_rgb_texture *albedo_map,
             i_monochrome_texture *roughness_map,
             i_rgb_texture *normal_map,
             i_monochrome_texture *ao_map)
            : albedo_map(albedo_map),
              roughness_map(roughness_map), ao_map(ao_map),
              normal_map(normal_map),
              to_local(affine_transform::identity()),
              to_world(affine_transform::identity()) {}

    i_object(const i_object &o) = default;

    void apply(const affine_transform &at) {
        to_world = to_world * at;
        to_local = to_local * at.inverse();
    }

    /**
     * Высчитывает пересечение с объектом
     * @param from_point - точка из которой выходит луч
     * @param v - направление луча
     * @return - локальные координаты пересечения
     */
    [[nodiscard]] virtual intersection *
    ray_intersection(const vec3f &from_point,
                     const vec3f &v,
                     const float &t_min,
                     const float &t_max) const = 0;
};


#endif //GLASSYRENDER_I_OBJECT_H
