//
// Created by Yakimov on 18.10.2019.
//

#ifndef GLASSYRENDER_AFFINE_TRANSFORM_H
#define GLASSYRENDER_AFFINE_TRANSFORM_H

#include <matrix.h>
#include <cmath>

typedef matrix<4, 4, float> affine_transform;

class affine_transform_factory {
public:
    static inline affine_transform move(const vec3f &p);

    static inline affine_transform to_point(const vec3f &from, const vec3f &to);

    static inline affine_transform rotate(float phi, const vec3f &axis_p, const vec3f &axis_v);

    static inline affine_transform rotateX(float phi, const vec3f &p);

    static inline affine_transform rotateY(float phi, const vec3f &p);

    static inline affine_transform rotateZ(float phi, const vec3f &p);

    static inline affine_transform stretch(const vec3f &p);

    static inline affine_transform to_coords_center(const vec3f &p);

private:
    static inline float to_radians(float degrees) {
        return degrees * M_PI / 180;
    }
};

affine_transform affine_transform_factory::to_point(const vec3f &from, const vec3f &to) {
    return affine_transform_factory::move(to - from);
}

affine_transform affine_transform_factory::move(const vec3f &p) {
    affine_transform res = affine_transform::identity();
    for (size_t i = 3; i--;) {
        res[i][3] = p[i];
    }
    return res;
}

affine_transform affine_transform_factory::rotate(float phi, const vec3f &axis_p, const vec3f &axis_v) {
    affine_transform T = to_coords_center(axis_p),
            Tinv = move(axis_p);
    auto V1 = vec<2, float>{axis_v[0], axis_v[1]}.normalized_copy();
    float C1 = V1[0];
    float S1 = V1[1];
    affine_transform R1 = {
            C1, S1, 0, 0,
            -S1, C1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
    affine_transform R1inv = R1.transpose();

    auto V2 = vec<2, float>{axis_v[1], axis_v[2]}.normalized_copy();
    float C2 = V2[0];
    float S2 = V2[1];
    affine_transform R2 = {
            1, 0, 0, 0,
            0, C2, S2, 0,
            0, -S2, C2, 0,
            0, 0, 0, 1
    };
    affine_transform R2inv = R2.transpose();
    float rad = to_radians(phi);
    float C3 = cos(rad);
    float S3 = sin(rad);

    affine_transform R3 = {
            C3, 0, S3, 0,
            0, 1, 0, 0,
            -S3, 0, C3, 0,
            0, 0, 0, 1
    };

    return T * R1 * R2 * R3 * R2inv * R1inv * Tinv  ;
}

affine_transform affine_transform_factory::to_coords_center(const vec3f &p) {
    return affine_transform_factory::move(-1 * p);
}

affine_transform affine_transform_factory::stretch(const vec3f &p) {
    affine_transform res = affine_transform::identity();
    for (size_t i = 3; i--;) {
        res[i][i] = p[i];
    }
    return res;
}

affine_transform affine_transform_factory::rotateX(float phi, const vec3f &p) {
    float rad = to_radians(phi);
    float C = cos(rad);
    float S = sin(rad);
    affine_transform rotate = {
            1, 0, 0, 0,
            0, C, S, 0,
            0, -S, C, 0,
            0, 0, 0, 1
    };
    auto to_center = to_coords_center(p);
    return move(p) * rotate * to_center;
}

affine_transform affine_transform_factory::rotateY(float phi, const vec3f &p) {
    float rad = to_radians(phi);
    float C = cos(rad);
    float S = sin(rad);
    affine_transform rotate = {
            C, 0, S, 0,
            0, 1, 0, 0,
            -S, 0, C, 0,
            0, 0, 0, 1
    };
    auto to_center = to_coords_center(p);
    return move(p) * rotate * to_center;
}

affine_transform affine_transform_factory::rotateZ(float phi, const vec3f &p) {
    float rad = to_radians(phi);
    float C = cos(rad);
    float S = sin(rad);
    affine_transform rotate = {
            C, S, 0, 0,
            -S, C, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    };
    auto to_center = to_coords_center(p);
    return move(p) * rotate * to_center;
}

#endif //GLASSYRENDER_AFFINE_TRANSFORM_H
