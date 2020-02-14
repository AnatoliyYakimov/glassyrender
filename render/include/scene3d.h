//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_SCENE3D_H
#define GLASSYRENDER_SCENE3D_H


#include <vector>
#include <windows.h>
#include <viewport.h>
#include <model.h>
#include <matrix.h>
#include <brdf.h>

class scene3d {
public:
    float ambient_light = 0.0f;
    float gamma = 2.2;
    float camera_exposure = 1;
    BRDF brdf;
    model model;
    viewport viewport;
    scene3d(int W, int H, float d);
    void clear(HDC);
    void draw_scene(HDC);
    void recompute_size(int H, int W);
private:
    std::vector<vec3f> frame_buffer;
    void apply_tone_mapping(int H, int W);
    void apply_gamma_correction(int H, int W);
    void render_scene(int H, int W);
    vec3f trace_ray(const vec3f &from_point, const vec3f& v);
};




#endif //GLASSYRENDER_SCENE3D_H
