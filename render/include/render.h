//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_RENDER_H
#define GLASSYRENDER_RENDER_H


#include <memory>
#include <vector>
#include <windows.h>
#include <viewport.h>
#include <scene.h>
#include <matrix.h>
#include <brdf.h>
#include <abstract_image.h>
#include <cook_torrance.h>
#include <render_options.h>

using std::vector;
using std::unique_ptr;

class render : public singleton {
public:

    static render &get_instance();

    abstract_image render_image();

    void move_cam(const affine_transform &at) {
        _viewport->apply(at);
    }

    render();
private:
    static render *instance;
    BRDF brdf;
    unique_ptr<viewport> _viewport;
    vec3f_arr frame_buffer;
    const render_options &opts = render_options::get_instance();



    void recompute_size();
    void apply_tone_mapping();
    void apply_gamma_correction();
    void render_scene();
    vec3f trace_ray(const vec3f &from_point, const vec3f& v);

};




#endif //GLASSYRENDER_RENDER_H
