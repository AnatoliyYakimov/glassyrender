

#ifndef GLASSYRENDER_ABSTRACT_IMAGE_heigth
#define GLASSYRENDER_ABSTRACT_IMAGE_heigth

#include <cmath>
#include <math/vec.h>

template <typename pixel_t>
class i_image {
protected:
    int width;
    int height;
public:

    i_image() : width(-1), height(-1) {}

    i_image(int width, int height) : width(width), height(height) {}

    virtual pixel_t &pixel_at(size_t x, size_t y) = 0;

    virtual const pixel_t &pixel_at(size_t x, size_t y) const = 0;

    int get_width() const {
        return width;
    }

    int get_height() const {
        return height;
    }
};

template <typename pixel_t>
class basic_image : virtual public i_image<pixel_t> {
protected:
    std::vector<pixel_t> data;

public:
    basic_image(std::vector<pixel_t> data, int width, int height) {
        this->data = move(data);
        this->width = width;
        this->height = height;
    }

    basic_image(basic_image &&img) noexcept {
        this->width = img.width;
        this->height = img.height;
        data = std::move(img.data);
    }

    basic_image(const basic_image& img) = delete;

    basic_image& operator=(const basic_image& img) = delete;
    basic_image& operator=(basic_image&& img) noexcept {
        this->width = img.width;
        this->height = img.height;
        data = std::move(img.data);
        return *this;
    }

    pixel_t &pixel_at(size_t x, size_t y) override {
        return data[x + y * this->width];
    }

    [[nodiscard]] const pixel_t &pixel_at(size_t x, size_t y) const {
        return data[x + y * this->width];
    }

    void set_data(const std::vector<pixel_t> &data, int w, int h) {
        basic_image::data = data;
        this->width = w;
        this->height = h;
    }

    [[nodiscard]] const std::vector<pixel_t> &get_data() const {
        return data;
    }

};

typedef vec<3, float> rgb_pixel;
typedef basic_image<vec3f> image_rgb;
typedef basic_image<float> image_mono;

#endif //GLASSYRENDER_ABSTRACT_IMAGE_heigth
