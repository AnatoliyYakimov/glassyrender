//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_POLYGONAL_OBJECT_H
#define GLASSYRENDER_POLYGONAL_OBJECT_H

#include <memory>
#include <objects/i_object.h>
#include <vector_utils.h>

using std::unique_ptr;
using std::vector;

class face {
public:
    vec3i v;
    vec3i vt;
    vec3i vn;

    face() = default;

    face(const face &f) : v(f.v), vt(f.vt), vn(f.vn) {}

    face(face &&f)
            : v(std::move(f.v)), vt(std::move(f.vt)), vn(std::move(f.vn)) {}

    face(const vec3i &v, const vec3i &vt, const vec3i &vn)
            : v(v), vt(vt), vn(vn) {}

    face(vec3i &&v, vec3i &&vt, vec3i &&vn)
            : v(v), vt(vt), vn(vn) {}
};

class polygonal_object : public i_object {
protected:

    unique_ptr <vec3f_arr> vertices;
    unique_ptr <vector<vec2f>> t_vertices;
    unique_ptr <vec3f_arr> n_vertices;
    unique_ptr <vector<face>> faces;

public:

    polygonal_object(const material_sp &_mat,
                     vec3f_arr *vertices,
                     vector<vec2f> *tVertices,
                     vec3f_arr *nVertices,
                     vector<face> *faces)
            : i_object(_mat),
              vertices(vertices),
              t_vertices(tVertices),
              n_vertices(nVertices),
              faces(faces) {}

    intersection *ray_intersection(const vec3f &from_point,
                                   const vec3f &dir,
                                   const float &t_min,
                                   const float &t_max) const override {
        struct _is {
            float d;
            vec2f *vt;
            const vec3f *vn;
        };
        const vec3f o_local = to_local * from_point;
        const vec3f v_local = to_local * dir;
        vector<_is> is;
        for (const auto &face : *faces) {
            const vec3f &a = (*vertices)[face.v[0] - 1];
            const vec3f &b = (*vertices)[face.v[1] - 1];
            const vec3f &c = (*vertices)[face.v[2] - 1];

            vec3f e1 = b - a;
            vec3f e2 = c - a;

            vec3f pvec = vector_utils<float>::vector_product(v_local, e2);
            float  det = e1 * pvec;

            if (det < 1e-8 && det > -1e-8) {
                continue;
            }

            float inv_det = 1.0 / det;
            vec3f tvec = o_local - a;

            float u = tvec * pvec * inv_det;
            if (u < 0 || u > 1) {
                continue;
            }

            vec3f qvec = vector_utils<float>::vector_product(tvec, e1);
            float v = v_local * qvec * inv_det;
            if (v < 0 || v + u > 1) {
                continue;
            }

            vec2f vt = interpolate_texture_coords(face, u, v);
            vec3f vn = interpolate_normal(face, u, v);
            float t = e2 * qvec * inv_det;

            is.push_back(_is{t, &vt, &vn});
        };
        if (is.size() == 0) {
            return nullptr;
        }
        const _is *min = &is[0];
        for (const _is &i : is) {
            if (i.d < min->d) {
                min = &i;
            }
        }
        vec3f p_world = to_world * (o_local + v_local * min->d);
        const vec2f &vt = *(min->vt);
        const vec3f &normal = *(min->vn);
        vec3f albedo = _material->get_albedo()->texture_at_point(vt);
        float roughness = _material->get_roughness()->texture_at_point(vt);
        float ao = _material->get_ao()->texture_at_point(vt);
        return new intersection(
                p_world,
                normal,
                vt,
                min->d);
    }

private:

    vec3f interpolate_normal(const face &f, float u, float v) const {
        const vec3f &a = (*n_vertices)[f.vn[0] - 1];
        const vec3f &b = (*n_vertices)[f.vn[1] - 1];
        const vec3f &c = (*n_vertices)[f.vn[2] - 1];
        vec3f normal = c * u + b * v + (1 - u - v) * a;
        return normal;
    }

    vec2f interpolate_texture_coords(const face &f, float u, float v) const {
        const vec2f &a = (*t_vertices)[f.vt[0] - 1];
        const vec2f &b = (*t_vertices)[f.vt[1] - 1];
        const vec2f &c = (*t_vertices)[f.vt[2] - 1];
        vec2f vt = c * v + b * u + (1 - u - v) * a;
        return vt;
    }
};

#endif //GLASSYRENDER_POLYGONAL_OBJECT_H
