//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_VIEWPORT_H
#define GLASSYRENDER_VIEWPORT_H


#include <functional>
#include "../entities/affine_transform.h"
#include "../entities/vector_utils.h"

class viewport {
private:
    affine_transform to_world;
    vec3f Vy = {0, 1, 0};
    vec3f Vx = {1, 0, 0};
    const float L = -0.5f;
    const float T = 0.5f;
    float divider = 1.0f;

    inline point2f camera_to_viewport(const int &u, const int &v) {
        float x = L + u * divider;
        float y = T - v * divider;
        return {x, y};
    }

public:
    UINT width;
    UINT height;
    vec3f camera_pos;
    vec3f origin_pos;
    float d;

    viewport(int, int, float);

    void recompute_size(int, int);

    void apply(const affine_transform &at);

    [[nodiscard]] vec3f get_camera_pos() const {
        return camera_pos;
    }

    auto screen_to_world_function() {
        return [this](int u, int v) -> vec3f {
            const point2f Pv = camera_to_viewport(u, v);
            const vec3f Pw = origin_pos + Pv[0] * Vx + Pv[1] * Vy;
            return Pw - camera_pos;
        };

    };
};

#endif //GLASSYRENDER_VIEWPORT_H
