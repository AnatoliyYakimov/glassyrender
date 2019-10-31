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
    for (int u = 0; u < W; u++) {
        for (int v = 0; v < H; v++) {
            vec3f rgb = trace_ray(viewport.camera_pos, viewport.screen_to_world(u, v));
            SetPixel(dc, u, v, rgb.get_color_ref());
        }
    }
}


vec3f scene3d::trace_ray(const vec3f &fromPoint, const vec3f &V) {
    auto nearest = model.nearest_collision(fromPoint, V, 1, inf);
    if (nearest == nullptr) {
        return model.scene_color;
    }
    auto[collision_point, sphere] = *nearest;
    float intensity = ambient_light;
    for (const i_light_source *light : model.lights) {
        if (!model.any_collision(
                collision_point, light->direction(collision_point),  eps, inf)) {
            intensity += light->count_impact(sphere->norm(collision_point), collision_point);
        }
    }
    intensity = intensity > 1.0f ? 1.0f : intensity;
    delete nearest;
    vec3f rgb = intensity * sphere->col;
    return rgb;
}

