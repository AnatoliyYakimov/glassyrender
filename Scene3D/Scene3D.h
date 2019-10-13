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
    auto spheres = model.getSpheres();
    ARRAY_LIST<std::pair<float, const sphere&>> points;
    for (const auto & sphere : spheres) {
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
        return SCENE_COLOR;
    }
    auto pair = std::min_element(points.begin(), points.end(), [](std::pair<float, const sphere&> &p1, std::pair<float, const sphere&> &p2) {
        if (p1.first > p2.first) return 1;
        else return -1;
    }).base();
    auto v = pair->first * V;
    const point3f & p = point3f{v[0], v[1], v[2]};
    float intensity = 0;
    for(const auto & light : model.getLights()) {
        intensity += light->count_impact(pair->second, p);
    }
    intensity = intensity > 1.0f ? 1.0f : intensity;
    auto col = intensity * pair->second.col;
    return RGB((int)col[0], (int)col[1], (int)col[2]);
}


#endif //GLASSYRENDER_SCENE3D_H
