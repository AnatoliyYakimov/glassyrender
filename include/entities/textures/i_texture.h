//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_I_TEXTURE_H
#define GLASSYRENDER_I_TEXTURE_H

#include "../../../lib/tga/tga.hpp"
#include "../color/color_utils.h"
#include "texture_map_loader.h"

class i_texture {
public:
    virtual vec3f texture_at_point(const vec2f &p) = 0;
};

class uniform_texture : public i_texture {
    vec3f val;
public:
    explicit uniform_texture(const vec3f &v) : val(v) {}

    uniform_texture(const uniform_texture &ut) : uniform_texture(ut.val) {}

    vec3f texture_at_point(const vec2f &p) override {
        return val;
    }
};

class simple_texture : public i_texture {
protected:
    int width = -1;
    int height = -1;
    std::shared_ptr<std::vector<vec3f>> texture_map;
public:
    simple_texture(std::string file_path, bool apply_gamma = false, float gamma = 1.0f) {
        tga::TGA tgaImg;
        tgaImg.Load(file_path);
        width = tgaImg.GetWidth();
        height = tgaImg.GetHeight();
        texture_map.reset((texture_map_loader::load_tga(tgaImg, apply_gamma, gamma)));
    }

    vec3f texture_at_point(const vec2f &p) override {
        int x = p[0] * width;
        int y = p[1] * height;
        return (*texture_map)[x + y * width];
    }
};

#endif //GLASSYRENDER_I_TEXTURE_H
