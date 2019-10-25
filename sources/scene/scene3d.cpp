//
// Created by Yakimov on 25.10.2019.
//
#include "../../include/scene/scene3d.h"


void scene3d::clear(HDC dc) {
    RECT r;
    GetClientRect(WindowFromDC(dc), &r);
    Rectangle(dc, 0, 0, r.right, r.bottom);
}

void scene3d::render_scene(HDC dc) {
    const int H = viewport.height;
    const int W = viewport.width;
    auto cam = viewport.get_camera_pos().to_point();
    auto f = viewport.screen_to_world_function();
    for (int u = 0; u < W; u++) {
        for (int v = 0; v < H; v++) {
            auto col = trace_ray(cam, f(u, v));
            SetPixel(dc, u, v, col);
        }
    }
}


COLORREF scene3d::trace_ray(const point3f &cam, const vec3f& V) {
    auto nearest = nearest_collision(model.getSpheres(), cam, V, 1, inf);
    if (!nearest) {
        delete nearest;
        return SCENE_COLOR;
    }
    auto [sphere, collision_point] = *nearest;
    float intensity = 0;
    for(const auto & light : model.getLights()) {
        intensity += light->count_impact(model.getSpheres(), *sphere, *collision_point);
    }
    intensity = intensity > 1.0f ? 1.0f : intensity;
    delete nearest;
    return get_color_ref(intensity * sphere->col);
}