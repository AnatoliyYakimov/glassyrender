//
// Created by Yakimov on 25.10.2019.
//
#include "../../include/scene/scene3d.h"


void scene3d::clear(HDC dc) {
    RECT r;
    GetClientRect(WindowFromDC(dc), &r);
    Rectangle(dc, 0, 0, r.right, r.bottom);
}

scene3d::scene3d(int W, int H, float d)  : model(), viewport(W, H, d), frame_buffer(H * W) {
    frame_buffer.reserve(W * H);
}


void scene3d::recompute_size(int H, int W) {
    viewport.recompute_size(H, W);
    frame_buffer.reserve(H * W);
}

void scene3d::draw_scene(HDC dc) {
    const int H = viewport.height;
    const int W = viewport.width;
    render_scene(H, W);
    apply_tone_mapping(H, W);
    apply_gamma_correction(H, W);
    for (int u = 0; u < W; u++) {
        for (int v = 0; v < H; v++) {
            SetPixel(dc, u, v, frame_buffer[v + u * H].get_color_ref());
        }
    }
}

void scene3d::render_scene(int H, int W) {
    for (int u = 0; u < W; u++) {
        for (int v = 0; v < H; v++) {
            frame_buffer[v + u * H] = trace_ray(viewport.camera_pos, viewport.screen_to_world(u, v));
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
//    intensity = intensity > 1.0f ? 1.0f : intensity;
    delete nearest;
    vec3f rgb = intensity * sphere->col;
    return rgb;
}

void scene3d::apply_tone_mapping(int H, int W) {
    vec3f unit = {1, 1, 1};
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            vec3f &v = frame_buffer[j + H * i];
            v = unit - exp(-camera_exposure * v);
        }
    }
}

void scene3d::apply_gamma_correction(int H, int W) {
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            frame_buffer[j + H * i] = frame_buffer[j + H * i].pow(1 / gamma);
        }
    }
}

