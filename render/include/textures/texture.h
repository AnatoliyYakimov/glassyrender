//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_TEXTURE_H
#define GLASSYRENDER_TEXTURE_H

#include <memory>
#include <textures/texture_map_loader.h>

template<typename T>
class base_texture {
protected:
    base_texture() = default;
public:
    virtual T texture_at_point(const vec2f &p) = 0;
    base_texture(const base_texture &bt) = delete;
};

template<typename T>
class mapped_base_texture : public base_texture<T> {
private:
    mapped_base_texture() = default;
public:
    static std::shared_ptr<base_texture<T>> load(std::string &file_path, bool apply_gamma = false, float gamma = 1.0f) {}
};

template <>
class mapped_base_texture<float> : public base_texture<float> {
protected:
    int width = -1;
    int height = -1;
    std::unique_ptr<std::vector<float>> texture_map;

public:
    mapped_base_texture(std::string &file_path, bool apply_gamma = false, float gamma = 1.0f) {
        auto[data, w, h] = texture_map_loader::load_tga_monochrome(file_path, apply_gamma, gamma);
        texture_map.reset(data);
        width = w;
        height = h;
    }

    static std::shared_ptr<base_texture<float>> load(std::string &file_path, bool apply_gamma = false, float gamma = 1.0f) {
        return std::make_shared<mapped_base_texture<float>>(file_path, apply_gamma, gamma);
    }

    float texture_at_point(const vec2f &p) override {
        int x = p[0] * width;
        int y = p[1] * height;
        return (*texture_map)[x + y * width];
    }
};



template <>
class mapped_base_texture<vec3f> : public base_texture<vec3f> {
protected:
    int width = -1;
    int height = -1;
    std::unique_ptr<vec3f_arr> texture_map;


public:
    mapped_base_texture(std::string &file_path, bool apply_gamma = false, float gamma = 1.0f) {
        auto[data, w, h] = texture_map_loader::load_tga_rgb(file_path, apply_gamma, gamma);
        texture_map.reset(data);
        width = w;
        height = h;
    }

    static std::shared_ptr<base_texture<vec3f>> load(std::string &file_path, bool apply_gamma = false, float gamma = 1.0f) {
        return std::make_shared<mapped_base_texture<vec3f>>(file_path, apply_gamma, gamma);
    }

    vec3f texture_at_point(const vec2f &p) override {
        int x = p[0] * width;
        int y = p[1] * height;
        return (*texture_map)[x + y * width];
    }

    friend class std::shared_ptr<mapped_base_texture<vec3f>>;
};

template <typename T>
class uniform_base_texture : public base_texture<T> {
public:
    static std::shared_ptr<base_texture<T>> get(T value) {}
    T texture_at_point(const vec2f &p) override {
        return 0;
    }
};

template <>
class uniform_base_texture<float> : public base_texture<float> {
protected:
    float val;
public:
    uniform_base_texture<float>(const float &v) : val(v) {}

    static std::shared_ptr<base_texture<float>> get(float value) {
        return std::make_shared<uniform_base_texture<float>>(value);
    }

    float texture_at_point(const vec2f &p) override {
        return val;
    }
};

template <>
class uniform_base_texture<vec3f> : public base_texture<vec3f> {
private:
    vec3f val;
public:
    uniform_base_texture<vec3f>(const vec3f &v) : val(v) {}

    static std::shared_ptr<base_texture<vec3f>> get(vec3f value) {
        return std::make_shared<uniform_base_texture<vec3f>>(value);
    }

    vec3f texture_at_point(const vec2f &p) override {
        return val;
    }
};

typedef base_texture<vec3f> texture_rgb;
typedef base_texture<float> texture_mono;

typedef mapped_base_texture<vec3f> mapped_texture_rgb;
typedef mapped_base_texture<float> mapped_texture_mono;

typedef uniform_base_texture<vec3f> uniform_texture_rgb;
typedef uniform_base_texture<float> uniform_texture_mono;

#endif //GLASSYRENDER_I_RGB_TEXTURE_H
