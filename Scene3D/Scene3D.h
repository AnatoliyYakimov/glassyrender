//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_SCENE3D_H
#define GLASSYRENDER_SCENE3D_H


#include <vector>
#include <windows.h>
#include "viewport.h"
#include "Model.h"

class Scene3D {
public:
    Model model;
    viewport canvas;
    Scene3D(int, int);
    void clear(HDC);
    void render_scene(HDC);
private:
    const color* trace_ray(const vec3f& V);
    constexpr static COLORREF SCENE_COLOR = RGB(255, 255, 255);
};

Scene3D::Scene3D(int W, int H) : model(), canvas(W, H) {

}

void Scene3D::clear(HDC dc) {
    RECT r;
    GetClientRect(WindowFromDC(dc), &r);
    Rectangle(dc, 0, 0, r.right, r.bottom);
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-signed-bitwise"
void Scene3D::render_scene(HDC dc) {
    const int H = canvas.Height;
    const int W = canvas.Width;
    auto f = canvas.transformer_function();
    for (int u = 0; u < W; u++) {
        for (int v = 0; v < H; v++) {
            auto *col = trace_ray(f(u, v));

            COLORREF colorRef = col ? RGB((*col)[0], (*col)[1], (*col)[2]) : SCENE_COLOR;
            SetPixel(dc, u, v, colorRef);
        }
    }
}
#pragma clang diagnostic pop

const color* Scene3D::trace_ray(const vec3f& V) {
    auto spheres = model.getSpheres();
    for (const auto & sphere : spheres) {
        auto [t1, t2] = sphere.ray_collision(canvas.O, V);
        if (t1 >= 1 || t2 >= 1) {
            return &sphere.col;
        }
    }
    return nullptr;
}


#endif //GLASSYRENDER_SCENE3D_H
