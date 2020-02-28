//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_POLYGONAL_OBJECT_H
#define GLASSYRENDER_POLYGONAL_OBJECT_H

#include <memory>
#include <utility>
#include <objects/i_object.h>
#include <math/vector_utils.h>

using std::unique_ptr;
using std::vector;

struct face {
    vec3i v;
    vec3i vt;
    vec3i vn;
};

class polygonal_object : public i_object {
protected:

    vec3f_arr vertices;
    vec3f_arr n_vertices;
    vec2f_arr t_vertices;
    vector<face> faces;

public:

    polygonal_object() : i_object() {}

    polygonal_object(polygonal_object &&obj) : i_object(std::move(obj)), vertices(std::move(obj.vertices)),
                                               t_vertices(std::move(obj.t_vertices)),
                                               n_vertices(std::move(obj.n_vertices)),
                                               faces(std::move(obj.faces)) {}

    polygonal_object(const material_sp &_mat,
                     vec3f_arr vertices,
                     vec2f_arr tVertices,
                     vec3f_arr nVertices,
                     vector<face> faces)
            : i_object(_mat),
              vertices(std::move(vertices)),
              t_vertices(std::move(tVertices)),
              n_vertices(std::move(nVertices)),
              faces(std::move(faces)) {}

    intersection *ray_intersection(const vec3f &from_point,
                                   const vec3f &dir,
                                   const float &t_min,
                                   const float &t_max) const override;

    const vec3f_arr &get_vertices() const {
        return vertices;
    }

    void set_vertices(vec3f_arr _vertices) {
        polygonal_object::vertices = move(_vertices);
    }

    const vec3f_arr &get_n_vertices() const {
        return n_vertices;
    }

    void set_n_vertices(vec3f_arr _n_vertices) {
        polygonal_object::n_vertices = move(_n_vertices);
    }

    const vec2f_arr &get_t_vertices() const {
        return t_vertices;
    }

    void set_t_vertices(vec2f_arr _t_vertices) {
        polygonal_object::t_vertices = move(_t_vertices);
    }

    const vector<face> &get_faces() const {
        return faces;
    }

    void set_faces(vector<face> _faces) {
        polygonal_object::faces = move(_faces);

    }

private:

    vec3f interpolate_normal(const face &f, float u, float v) const;

    vec2f interpolate_texture_coords(const face &f, float u, float v) const;
};

#endif //GLASSYRENDER_POLYGONAL_OBJECT_H
