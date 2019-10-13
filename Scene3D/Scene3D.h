//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_SCENE3D_H
#define GLASSYRENDER_SCENE3D_H


#include <vector>
#include <windows.h>
#include "viewport.h"
#include "model.h"

class Scene3D {
public:
    model model;
    viewport canvas;
    Scene3D(int, int);
    void clear(HDC);
    void render_scene(HDC);
    std::pair<const sphere*, const point3f*>* nearest_collision(const vec3f &V);
private:
    COLORREF trace_ray(const vec3f& V);
    constexpr static COLORREF SCENE_COLOR = RGB(255, 255, 255);
};

Scene3D::Scene3D(int W, int H) : model(), canvas(W, H) {

}

void Scene3D::clear(HDC dc) {
    RECT r;
    GetClientRect(WindowFromDC(dc), &r);
    Rectangle(dc, 0, 0, r.right, r.bottom);
}

void Scene3D::render_scene(HDC dc) {
    const int H = canvas.Height;
    const int W = canvas.Width;
    auto f = canvas.transformer_function();
    for (int u = 0; u < W; u++) {
        for (int v = 0; v < H; v++) {
            auto col = trace_ray(f(u, v));
            SetPixel(dc, u, v, col);
        }
    }
}


COLORREF Scene3D::trace_ray(const vec3f& V) {
    auto nearest = nearest_collision(V);
    if (!nearest) {
        delete nearest;
        return SCENE_COLOR;
    }
    auto [sphere, collision_point] = *nearest;
    float intensity = 0;
    for(const auto & light : model.getLights()) {
        intensity += light->count_impact(*sphere, *collision_point);
    }
    intensity = intensity > 1.0f ? 1.0f : intensity;
    delete nearest;
    return get_color_ref(intensity * sphere->col);
}

std::pair<const sphere *, const point3f *>* Scene3D::nearest_collision(const vec3f &V) {
    auto spheres = model.getSpheres();
    ARRAY_LIST<std::pair<float, const sphere&>> points;
    for (const auto &sphere : spheres) {
        auto [t1, t2] = sphere.ray_collision(canvas.O, V);
        if (t1 > 1 || t2 > 1) {
            float min = 0;
            if (t1 > 1) {
                if (t2 > 1) {
                    min = t1 < t2 ? t1 : t2;
                } else {
                    min = t1;
                }
            } else {
                min = t2;
            }
            points.emplace_back(min, sphere);
        }
    }
    if (points.empty()){
        return nullptr;
    }
    const std::pair<float, const sphere&>* nearest = points.begin().base();
    for (const auto &item : points) {
        if (item.first < nearest->first) {
            nearest = &item;
        }
    }
    const point3f &p = (nearest->first * V).to_point();
    const sphere &s = nearest->second;
    return new std::pair<const sphere *, const point3f *>(&s, &p);
}


#endif //GLASSYRENDER_SCENE3D_H
