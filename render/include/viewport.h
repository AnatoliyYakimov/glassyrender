//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_VIEWPORT_H
#define GLASSYRENDER_VIEWPORT_H


#include <functional>
#include <affine_transform.h>
#include <vector_utils.h>

class viewport {
private:
    affine_transform to_world;
    vec3f Vy = vec3f{0, 1, 0};
    vec3f Vx = vec3f{1, 0, 0};
    const float L = -0.5f;
    const float T = 0.5f;
    float divider = 1.0f;
    float FOV;

    inline vec2f camera_to_viewport(const int &u, const int &v) {
        float x = L + u * divider;
        float y = T - v * divider;
        return vec2f{x, y};
    }

    vec3f camera_pos;
    vec3f origin_pos;
public:

    viewport(const float FOV) : camera_pos({0, 0, -FOV}),
                                origin_pos({0,0,0}),
                                to_world(affine_transform::identity()),
                                FOV(FOV) {
    }

    void recompute_size(int, int);

    [[nodiscard]] const vec3f &get_camera_pos() const {
        return camera_pos;
    }

    void apply(const affine_transform &at);

    inline vec3f screen_to_world(const int &u, const int &v) {
            const vec2f Pv = camera_to_viewport(u, v);
            const vec3f Pw = origin_pos + Pv[0] * Vx + Pv[1] * Vy;
            return Pw - camera_pos;
    };
};

#endif //GLASSYRENDER_VIEWPORT_H
