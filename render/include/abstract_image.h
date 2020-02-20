

#ifndef GLASSYRENDER_ABSTRACT_IMAGE_heigth
#define GLASSYRENDER_ABSTRACT_IMAGE_heigth

#include <image.hpp>
#include <cmath>

class rgb_pixel {
private:
    static constexpr uint8_t COLORS_8_BIT = 255;
    static constexpr uint16_t COLORS_16_BIT = 65535;
    float data[3];
public:
    rgb_pixel() : data() {
        for (size_t i = 3; i--;) {
            data[i] = 0.0f;
        }
    }

    rgb_pixel(float r, float g, float b) : data() {
        data[0] = r;
        data[1] = g;
        data[2] = b;
    }

    rgb_pixel(const rgb_pixel &pix) : data() {
        for (size_t i = 3; i--;) {
            data[i] = pix[i];
        }
    }

    rgb_pixel &operator=(const rgb_pixel &pix) {
        for (size_t i = 3; i--;) {
            data[i] = pix[i];
        }
        return *this;
    }

    [[nodiscard]] png::rgb_pixel to_png_rgb_pixel8() const {
        uint8_t r = red() * COLORS_8_BIT, g = green() * COLORS_8_BIT, b = blue() * COLORS_8_BIT;
        return png::rgb_pixel{r, g, b};
    }

    [[nodiscard]] png::rgb_pixel_16 to_png_rgb_pixel16() const {
        uint16_t r = red() * COLORS_16_BIT, g = green() * COLORS_16_BIT, b = blue() * COLORS_16_BIT;
        return png::rgb_pixel_16{r, g, b};
    }

    [[nodiscard]] float red() const {
        return data[0];
    }

    [[nodiscard]] float green() const {
        return data[1];
    }


    [[nodiscard]] float blue() const {
        return data[2];
    }

    float &operator[](size_t idx) {
        assert(idx < 3);
        return data[idx];
    }

    const float &operator[](size_t idx) const {
        assert(idx < 3);
        return data[idx];
    }
};


class abstract_image {
private:
    std::vector<rgb_pixel> data;
    int width;
    int height;

public:
    abstract_image(std::vector<rgb_pixel> data, int width, int height) : data(std::move(data)), width(width), height(height) { }

    abstract_image(abstract_image &&img) noexcept {
        width = img.width;
        height = img.height;
        data = std::move(img.data);
    }

    abstract_image(const abstract_image& img) = delete;

    abstract_image& operator=(const abstract_image& img) = delete;
    abstract_image& operator=(abstract_image&& img) noexcept {
        width = img.width;
        height = img.height;
        data = std::move(img.data);
        return *this;
    }

    png::image<png::rgb_pixel>* to_png8() {
        auto *png = new png::image<png::rgb_pixel>(width, height);
        auto &buf = png->get_pixbuf();
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                buf[j][i] = data[j + i * height].to_png_rgb_pixel8();
            }
        }
        return png;
    }

    png::image<png::rgb_pixel_16>* to_png16() {
        auto *png = new png::image<png::rgb_pixel_16>(width, height);
        auto &buf = png->get_pixbuf();
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                buf[j][i] = data[j + i * height].to_png_rgb_pixel16();
            }
        }
        return png;
    }

    rgb_pixel &pixel_at(size_t x, size_t y) {
        return data[x + y * width];
    }

    [[nodiscard]] const rgb_pixel &pixel_at(size_t x, size_t y) const {
        return data[x + y * width];
    }

    void set_data(const std::vector<rgb_pixel> &data) {
        abstract_image::data = data;
    }

    [[nodiscard]] const std::vector<rgb_pixel> &get_data() const {
        return data;
    }

    [[nodiscard]] int get_width() const {
        return width;
    }

    [[nodiscard]] int get_height() const {
        return height;
    }

};

#endif //GLASSYRENDER_ABSTRACT_IMAGE_heigth
