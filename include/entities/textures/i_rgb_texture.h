//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_I_RGB_TEXTURE_H
#define GLASSYRENDER_I_RGB_TEXTURE_H

#include <memory>
#include "../../../filesystem/include/tga.h"
#include "../color/color_utils.h"
#include "texture_map_loader.h"

class i_rgb_texture {
public:
    virtual vec3f texture_at_point(const vec2f &p) = 0;
};

class uniform_rgb_texture : public i_rgb_texture {
    vec3f val;
public:
    explicit uniform_rgb_texture(const vec3f &v) : val(v) {}

    uniform_rgb_texture(const uniform_rgb_texture &ut) : uniform_rgb_texture(ut.val) {}

    vec3f texture_at_point(const vec2f &p) override {
        return val;
    }
};

class mapped_rgb_texture : public i_rgb_texture {
protected:
    int width = -1;
    int height = -1;
    std::shared_ptr<std::vector<vec3f>> texture_map;
public:
    explicit mapped_rgb_texture(std::string &file_path, bool apply_gamma = false, float gamma = 1.0f) {
        auto[data, w, h] = texture_map_loader::load_tga_rgb(file_path, apply_gamma, gamma);
        texture_map.reset(data);
        width = w;
        height = h;
    }

    vec3f texture_at_point(const vec2f &p) override {
        int x = p[0] * width;
        int y = p[1] * height;
        return (*texture_map)[x + y * width];
    }
};

#endif //GLASSYRENDER_I_RGB_TEXTURE_H
