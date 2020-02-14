//
// Created by Yakimov on 01.12.2019.
//

#include <tuple>
#include "texture_map_loader.h"

std::tuple<std::vector<vec3f> *, int, int>
texture_map_loader::load_tga_rgb(const std::string &file_path, bool apply_gamma, float gamma) {
    tga::TGA tga;
    tga.Load(file_path);
    const uint8_t *data = tga.GetData();
    float r, g, b;
    uint32_t k;
    const int width = tga.GetWidth();
    const int height = tga.GetHeight();
    auto* res = new std::vector<vec3f>(width * height);
    for (uint16_t i = 0; i < height; i++) {
        for (uint16_t j = 0; j < width; j++) {
            k = (j + i * width) * 3;
            r = data[k];
            g = data[k + 1];
            b = data[k + 2];
            vec3f col = vec3f{r, g, b} / 255.0f;
            if (apply_gamma) {
                col = col.pow(gamma);
            }
            (*res)[j + i * width] = col;
        }
    }
    return std::tie(res, width, height);
}

std::tuple<std::vector<float> *, int, int>
texture_map_loader::load_tga_monochrome(const std::string &file_path, bool apply_gamma, float gamma) {
    tga::TGA tga;
    tga.Load(file_path);
    const uint8_t *data = tga.GetData();
    float r, g, b;
    uint32_t k;
    const int width = tga.GetWidth();
    const int height = tga.GetHeight();
    auto* res = new std::vector<float>(width * height);
    for (uint16_t i = 0; i < height; i++) {
        for (uint16_t j = 0; j < width; j++) {
            k = (j + i * width);
            float col = data[k] / 255.0f;
            if (apply_gamma) {
                col = pow(col, gamma);
            }
            (*res)[j + i * width] = col;
        }
    }
    return std::tie(res, width, height);
}
