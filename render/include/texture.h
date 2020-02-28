

#ifndef GLASSYRENDER_TEXTURE_H
#define GLASSYRENDER_TEXTURE_H

#include <basic_image.h>

template<typename pixel_t>
class i_texture : virtual public i_image<pixel_t> {
public:
    i_texture() = default;

    virtual pixel_t &pixel_at(vec2f pos) = 0;

    virtual const pixel_t &pixel_at(vec2f pos) const = 0;
};

template <typename T>
class uniform_texture : virtual public i_texture<T> {
protected:
    T val;
public:
    uniform_texture() = default;

    explicit uniform_texture(T val) : val(val) {
        this->width = -1;
        this->height = -1;
    }

    T &pixel_at(size_t x, size_t y) override {
        return val;
    }

    const T &pixel_at(size_t x, size_t y) const override {
        return val;
    }

    T &pixel_at(vec2f pos) override {
        return val;
    }

    const T &pixel_at(vec2f pos) const override {
        return val;
    }
};

template<typename pixel_t>
class basic_texture : public basic_image<pixel_t>, virtual public i_texture<pixel_t> {
public:
    basic_texture(const std::vector<pixel_t> &data, int width, int height)
            : basic_image<pixel_t>(data, width, height) {}

    explicit basic_texture(basic_image<pixel_t> &&img) : basic_image<pixel_t>(std::move(img)) {}

    basic_texture(const basic_texture<pixel_t> &) = delete;

    pixel_t &pixel_at(vec2f pos) override {
        uint16_t x = i_image<pixel_t>::width * pos[0];
        while (x >= i_image<pixel_t>::width) {
            x -= i_image<pixel_t>::width;
        }
        uint16_t y = i_image<pixel_t>::height * pos[1];
        while (y >= i_image<pixel_t>::height) {
            y -= i_image<pixel_t>::height;
        }
        return basic_image<pixel_t>::pixel_at(x, y);
    }

    [[nodiscard]] const pixel_t &pixel_at(vec2f pos) const override {
        uint16_t x = i_image<pixel_t>::width * pos[0];
        while (x >= i_image<pixel_t>::width) {
            x -= i_image<pixel_t>::width;
        }
        uint16_t y = i_image<pixel_t>::height * pos[1];
        while (y >= i_image<pixel_t>::height) {
            y -= i_image<pixel_t>::height;
        }
        return basic_image<pixel_t>::pixel_at(x, y);
    }
};

typedef i_texture<vec3f> texture_rgb;
typedef i_texture<float> texture_mono;

typedef basic_texture<vec3f> mapped_texture_rgb;
typedef basic_texture<float> mapped_texture_mono;

typedef uniform_texture<vec3f> uniform_texture_rgb;
typedef uniform_texture<float> uniform_texture_mono;



#endif //GLASSYRENDER_TEXTURE_H
