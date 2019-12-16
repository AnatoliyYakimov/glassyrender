//
// Created by Yakimov on 07.12.2019.
//

#ifndef GLASSYRENDER_I_MONOCHROME_TEXTURE_H
#define GLASSYRENDER_I_MONOCHROME_TEXTURE_H


#include <vector>
#include <memory>
#include "../algebra/vec.h"
#include "../../../lib/tga/tga.hpp"
#include "texture_map_loader.h"

class i_monochrome_texture {
public:
    virtual float texture_at_point(const vec2f &p) = 0;
};

class uniform_monochrome_texture : public i_monochrome_texture {
    float val;
public:
    explicit uniform_monochrome_texture(const float &v) : val(v) {}

    uniform_monochrome_texture(const uniform_monochrome_texture &ut) : uniform_monochrome_texture(ut.val) {}

    float texture_at_point(const vec2f &p) override {
        return val;
    }
};

class mapped_monochrome_texture : public i_monochrome_texture {
protected:
    int width = -1;
    int height = -1;
    std::shared_ptr<std::vector<float>> texture_map;
public:
    explicit mapped_monochrome_texture(std::string &file_path, bool apply_gamma = false, float gamma = 1.0f) {
        auto[data, w, h] = texture_map_loader::load_tga_monochrome(file_path, apply_gamma, gamma);
        texture_map.reset(data);
        width = w;
        height = h;
    }

    float texture_at_point(const vec2f &p) override {
        int x = p[0] * width;
        int y = p[1] * height;
        return (*texture_map)[x + y * width];
    }
};


#endif //GLASSYRENDER_I_MONOCHROME_TEXTURE_H
