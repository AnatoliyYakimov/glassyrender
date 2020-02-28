

#ifndef GLASSYRENDER_PNG_UTILS_H
#define GLASSYRENDER_PNG_UTILS_H

#include <image.hpp>
#include <basic_image.h>

class png_utils {
private:
    static constexpr uint8_t COLORS_8_BIT = 255;
    static constexpr uint16_t COLORS_16_BIT = 65535;
public:
    static png::rgb_pixel to_rgb_pixel8(const rgb_pixel &pix) {
        uint8_t r = pix.r() * COLORS_8_BIT, g = pix.g() * COLORS_8_BIT, b = pix.b() * COLORS_8_BIT;
        return png::rgb_pixel{r, g, b};
    }

    static png::rgb_pixel_16 to_rgb_pixel16(const rgb_pixel &pix) {
        uint16_t r = pix.r() * COLORS_16_BIT, g = pix.g() * COLORS_16_BIT, b = pix.b() * COLORS_16_BIT;
        return png::rgb_pixel_16{r, g, b};
    }

    static png::image<png::rgb_pixel>* to_8bit(const image_rgb &img) {
        int width = img.get_width();
        int height = img.get_height();
        auto data = img.get_data();
        auto *png = new png::image<png::rgb_pixel>(width, height);
        auto &buf = png->get_pixbuf();
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                buf[j][i] = to_rgb_pixel8(data[j + i * height]);
            }
        }
        return png;
    }

    static png::image<png::rgb_pixel_16>* to_16bit(const image_rgb &img) {
        int width = img.get_width();
        int height = img.get_height();
        auto data = img.get_data();
        auto *png = new png::image<png::rgb_pixel_16>(width, height);
        auto &buf = png->get_pixbuf();
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                buf[j][i] = to_rgb_pixel16(data[j + i * height]);
            }
        }
        return png;
    }
};
#endif //GLASSYRENDER_PNG_UTILS_H
