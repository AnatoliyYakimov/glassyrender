//
// Created by Yakimov on 01.12.2019.
//

#include "texture_map_loader.h"

std::vector<vec3f>*
texture_map_loader::load_tga(const tga::TGA& tga, bool apply_gamma, float gamma) {
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
    return res;
}
