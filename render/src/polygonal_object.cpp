

#include <objects/polygonal_object.h>
#include <constants.h>

intersection *polygonal_object::ray_intersection(const vec3f &from_point,
                                                 const vec3f &dir,
                                                 const float &t_min,
                                                 const float &t_max) const {
    struct _is {
        float d;
        const face &f;
        float u, v;
        vec3f point;
    };
    const vec3f o_local = to_local * from_point;
    const vec3f v_local = to_local * dir;
    vector<_is> is;
    for (const auto &_face : faces) {
        const vec3f &a = vertices[_face.v[0] - 1];
        const vec3f &b = vertices[_face.v[1] - 1];
        const vec3f &c = vertices[_face.v[2] - 1];

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


        float t = e2 * qvec * inv_det;
        if (t < 0) {
            continue;
        }
        vec3f p_world = to_world * (o_local + v_local * t);
        float d = (p_world - from_point).norm();
        if (d > t_min && d < t_max) {
            is.push_back(_is{d, _face, u, v, p_world});
        }
    };
    if (is.empty()) {
        return nullptr;
    }
    const _is *min = &is[0];
    for (const _is &i : is) {
        if (i.d < min->d) {
            min = &i;
        }
    }

    float u = min->u;
    float v = min->v;
    vec2f vt = interpolate_texture_coords(min->f, u, v);
    vec3f vn = interpolate_normal(min->f, u, v);

    return new intersection(
            min->point,
            vn,
            vt,
            min->d);
}

vec3f
polygonal_object::interpolate_normal(const face &f, float u, float v) const {
    const vec3f &a = n_vertices[f.vn[0] - 1];
    const vec3f &b = n_vertices[f.vn[1] - 1];
    const vec3f &c = n_vertices[f.vn[2] - 1];
    vec3f normal = c * v + b * u + (1 - u - v) * a;
    return normal;
}

vec2f polygonal_object::interpolate_texture_coords(const face &f,
                                                   float u,
                                                   float v) const {
    const vec2f &a = t_vertices[f.vt[0] - 1];
    const vec2f &b = t_vertices[f.vt[1] - 1];
    const vec2f &c = t_vertices[f.vt[2] - 1];
    vec2f vt = c * v + b * u + (1 - u - v) * a;
    for (size_t i = 2; i--;) {
        if (vt[i] > (1.0f - eps)) {
            vt[i] = 1.0f - eps;
        }
    }
    return vt;
}
