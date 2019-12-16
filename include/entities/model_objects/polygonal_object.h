//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_POLYGONAL_OBJECT_H
#define GLASSYRENDER_POLYGONAL_OBJECT_H

#include <memory>
#include <boost/scoped_ptr.hpp>
#include "i_object.h"

using namespace std;
using namespace boost;

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
    scoped_ptr <vector<vec3f>> vertices;
    scoped_ptr <vector<vec2f>> t_vertices;
    scoped_ptr <vector<vec3f>> n_vertices;
    scoped_ptr <vector<face>> faces;
public:
    polygonal_object(vector<vec3f> *vertices,
                     vector<vec2f> *tVertices,
                     vector<vec3f> *nVertices,
                     vector<face> *faces)
            : vertices(vertices), t_vertices(tVertices), n_vertices(nVertices),
              faces(faces) {}

    polygonal_object(i_rgb_texture *albedoMap,
                     i_monochrome_texture *roughnessMap,
                     i_rgb_texture *normalMap,
                     i_monochrome_texture *aoMap,
                     vector<vec3f> *vertices,
                     vector<vec2f> *tVertices,
                     vector<vec3f> *nVertices,
                     vector<face> *faces)
            : i_object(albedoMap,
                       roughnessMap,
                       normalMap,
                       aoMap),
              vertices(vertices),
              t_vertices(tVertices),
              n_vertices(nVertices),
              faces(faces) {}

    intersection *ray_intersection(const vec3f &from_point,
                                   const vec3f &v,
                                   const float &t_min,
                                   const float &t_max) const override {
        struct _is {
            float d;
            vec2f *vt;
            const vec3f *vn;
        };
        const vec3f o_l = to_local * from_point;
        const vec3f v_local = to_local * v;
        vector<_is> is;
        for (const auto &face : *faces) {
            const vec3f &a = (*vertices)[face.v[0] - 1];
            const vec3f &b = (*vertices)[face.v[1] - 1];
            const vec3f &c = (*vertices)[face.v[2] - 1];
            affine_transform T;
            for (size_t j = 3; j--;) {
                T[j] = vec4f{a[j] - c[j], b[j] - c[j], c[j], 0};
            }
            T[3] = vec4f{0, 0, 0, 1};
            affine_transform Tinv = T.inverse();
            vec3f o = (Tinv * o_l.extend(0)).shrink();
            vec3f d = (Tinv * v_local.extend(0)).shrink();
            float t = -o[2] / d[2];
            if (t < t_min && t > t_max) {
                continue;
            }
            float u_l = o[0] + t * d[0];
            if (u_l < 0 || u_l > 1) {
                continue;
            }
            u_l += face.vt[0 - 1];
            float v_l = o[1] + t * d[1];
            if (v_l < 0 || v_l > 1) {
                continue;
            }
            v_l += face.vt[1 - 1];
            vec2f vt = vec2f{u_l, v_l};
            vec3f vn = interpolate_normal(face, u_l, v_l);
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
        vec3f p_world = to_world * (o_l + v_local * min->d);
        const vec2f &vt = *(min->vt);
        const vec3f &normal = *(min->vn);
        vec3f albedo = albedo_map->texture_at_point(vt);
        float roughness = roughness_map->texture_at_point(vt);
        float ao = ao_map->texture_at_point(vt);
        return new intersection(
                p_world,
                min->d,
                normal,
                albedo,
                roughness,
                ao);
    }

private:

    vec3f interpolate_normal(const face &f, float u, float v) const {
        const vec3f &a = (*n_vertices)[f.vn[0] - 1];
        const vec3f &b = (*n_vertices)[f.vn[1] - 1];
        const vec3f &c = (*n_vertices)[f.vn[2] - 1];
        float w = 1 - u - v;
        vec3f normal = a * u + b * v + (1 - u - v) * c;
        return normal;
    }
};

#endif //GLASSYRENDER_POLYGONAL_OBJECT_H
