//
// Created by Yakimov on 25.10.2019.
//
#include <render.h>
#include <cook_torrance.h>

render *render::instance = nullptr;

render &render::get_instance()  {
    if (render::instance == nullptr) {
        render::instance = new render();
    }
    return *instance;
}

void render::recompute_size() {
    frame_buffer.reserve(opts.width * opts.height);
    _viewport->recompute_size(opts.width, opts.height);
}


abstract_image render::render_image() {
    recompute_size();
    const int H = opts.height;
    const int W = opts.width;
    render_scene();
    apply_tone_mapping();
    apply_gamma_correction();
    std::vector<rgb_pixel> data(W * H);
    for (int u = 0; u < W; u++) {
        for (int v = 0; v < H; v++) {
            int pos = v + u * H;
            vec3f rgb = frame_buffer[pos];
            data[pos] = rgb_pixel(rgb[0], rgb[1], rgb[2]);
        }
    }
    return std::move(abstract_image(std::move(data), W, H));
}

void render::render_scene() {
    int W = opts.width;
    int H = opts.height;
    for (int u = 0; u < W; u++) {
        for (int v = 0; v < H; v++) {
            frame_buffer[v + u * H] = trace_ray(_viewport->get_camera_pos(), _viewport->screen_to_world(u, v).normalize());
        }
    }
}

vec3f render::trace_ray(const vec3f &from_point, const vec3f &v) {
    scene &s = scene::get_instance();
    auto opt = s.nearest_collision(from_point, v, 1, inf);

    if (!opt) {
        return s.scene_color;
    }
    const auto &mat = opt.value().first->get_material();
    const auto &is = opt.value().second;
    const vec3f &p = is.intersection_point;
    const vec2f &vt = is.texture_coords;
    vec3f albedo = mat->get_albedo()->texture_at_point(vt);
    float ao = mat->get_ao()->texture_at_point(vt);
    float roughness = mat->get_roughness()->texture_at_point(vt);
    //TODO Разобраться с Френелем
    vec3f frenel = albedo * (1 - roughness) * 0.4;
    vec3f _brdf_irradiance = brdf.count_irradiance(
            p,
            v.normalized_copy(),
            is.normal,
            albedo,
            frenel,
            roughness,
            ao);
    vec3f color = albedo * opts.ambient_light + _brdf_irradiance;
    return color;
}

void render::apply_tone_mapping() {
    const int H = opts.height;
    const int W = opts.width;
    vec3f unit = vec3f{1, 1, 1};
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            vec3f &v = frame_buffer[j + H * i];
            v = unit - exp(-opts.camera_exposure * v);
        }
    }
}

void render::apply_gamma_correction() {
    const int H = opts.height;
    const int W = opts.width;
    for (int i = 0; i < W; ++i) {
        for (int j = 0; j < H; ++j) {
            frame_buffer[j + H * i] = frame_buffer[j + H * i].pow(1 / opts.gamma);
        }
    }
}

render::render()  : singleton(), frame_buffer(), brdf(new GGX_distribution(), new SchlickGGX(), new schlicks_approximation()) {
    _viewport = std::make_unique<viewport>(opts.FOV);
    recompute_size();
}


