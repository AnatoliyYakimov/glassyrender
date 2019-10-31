//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_SCENE3D_H
#define GLASSYRENDER_SCENE3D_H


#include <vector>
#include <windows.h>
#include "viewport.h"
#include "model.h"
#include "../entities/matrix.h"

class scene3d {
public:
    float ambient_light = 0.0f;
    model model;
    viewport viewport;
    scene3d(int W, int H, float d) : model(), viewport(W, H, d) {};
    void clear(HDC);
    void render_scene(HDC);
private:
    vec3f trace_ray(const vec3f &fromPoint, const vec3f& V);
    constexpr static COLORREF SCENE_COLOR = RGB(255, 255, 255);
};




#endif //GLASSYRENDER_SCENE3D_H
