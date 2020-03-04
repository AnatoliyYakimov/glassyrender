//
// Created by Yakimov on 01.12.2019.
//

#ifndef GLASSYRENDER_TGA_UTILS_H
#define GLASSYRENDER_TGA_UTILS_H


#include <vector>
#include <tga.h>
#include <math/vec.h>
#include <basic_image.h>

template<typename T>
class tga_utils {
public:
    static image_rgb load_tga(const std::string &file_path,
                              bool apply_gamma = false,
                              float gamma = 1.0f);
};

template<>
class tga_utils<vec3f> {
public:
    static image_rgb load(const std::string &file_path,
                          bool apply_gamma = false,
                          float gamma = 1.0f) {
        tga::TGA tga;

        try {
            tga.Load(file_path);
        } catch (std::exception &e) {
            string str = "Error while loading TGA. Details:\n\t";
            str += e.what();
            throw std::runtime_error(str);
        }
        const uint8_t *data = tga.GetData();
        float r, g, b;
        uint32_t k, p;
        const int width = tga.GetWidth();
        const int height = tga.GetHeight();
        auto res = vec3f_arr(width * height);
        for (uint16_t i = 0; i < height; i++) {
            for (uint16_t j = 0; j < width; j++) {
                p = j + i * width;
                k = p * 3;
                r = data[k];
                g = data[k + 1];
                b = data[k + 2];
                vec3f col = vec3f{r, g, b} / 255.0f;
                if (apply_gamma) {
                    col = col.pow(gamma);
                }
                res[p] = col;
            }
        }
        return image_rgb(move(res), width, height);
    }
};

template<>
class tga_utils<float> {
public:
    static image_mono load(const std::string &file_path,
                           bool apply_gamma = false,
                           float gamma = 1.0f) {
        tga::TGA tga;
        try {
            tga.Load(file_path);
        } catch (std::exception &e) {
            string str = "Error while loading TGA. Details:\n\t";
            str += e.what();
            throw std::runtime_error(str);
        }
        const uint8_t *data = tga.GetData();
        uint32_t k, p;
        const int width = tga.GetWidth();
        const int height = tga.GetHeight();
        auto res = std::vector<float>(width * height);
        for (uint16_t i = 0; i < height; i++) {
            for (uint16_t j = 0; j < width; j++) {
                p = j + i * width;
                k = p * 3;
                float col = data[p] / 255.0f;
                if (apply_gamma) {
                    col = pow(col, gamma);
                }
                res[p] = col;
            }
        }
        return image_mono(move(res), width, height);
    }
};


#endif //GLASSYRENDER_TGA_UTILS_H
