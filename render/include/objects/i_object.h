//
// Created by Yakimov on 16.10.2019.
//

#ifndef GLASSYRENDER_I_OBJECT_H
#define GLASSYRENDER_I_OBJECT_H

#include <utility>
#include <vector>
#include <material.h>
#include <math/affine_transform.h>
#include <basic_image.h>

class intersection {
public:
    const vec3f intersection_point;
    const vec3f normal;
    const vec2f texture_coords;
    const float distance;

    intersection(const vec3f &intersection_point,
                 const vec3f &normal,
                 const vec2f &texture_coords,
                 const float distance)
            : intersection_point(intersection_point),
              normal(normal),
              texture_coords(texture_coords),
              distance(distance) {}

    intersection(const intersection &is) = default;

};

class obj_file_handler;

class i_object {
protected:
    affine_transform to_local;
    affine_transform to_world;
    material_sp _material;
public:

    i_object() : _material(nullptr),
                 to_local(affine_transform::identity()),
                 to_world(affine_transform::identity()) {}

    i_object(const i_object &obj) = delete;

    i_object(i_object &&obj) : _material(move(obj._material)),
                               to_local(obj.to_local),
                               to_world(obj.to_world) {}

    explicit i_object(material_sp mat)
            : _material(move(mat)),
              to_local(affine_transform::identity()),
              to_world(affine_transform::identity()) {}


    void apply(const affine_transform &at) {
        to_world = to_world * at;
        to_local = to_local * at.inverse();
    }

    virtual bool valid() {
        return (bool) _material;
    }

    void set_material(const material_sp &material) {
        _material = material;
    }

    [[nodiscard]] const material_sp &get_material() const {
        return _material;
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

typedef std::shared_ptr<i_object> obj_sp;
#endif //GLASSYRENDER_I_OBJECT_H
