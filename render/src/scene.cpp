//
// Created by Yakimov on 30.09.2019.
//

#include <algorithm>
#include <scene.h>

scene *scene::instance = nullptr;

scene &scene::get_instance() {
    if (scene::instance == nullptr) {
        scene::instance = new scene();
    }
    return *instance;
}



boost::optional<pair<obj_sp, intersection>>
    scene::nearest_collision(const vec3f &fromPoint, const vec3f &V, float t_min, float t_max) const {
    std::vector<pair<obj_sp, intersection>> intersections;
    for (const auto &object : objects) {
        intersection *is = object->ray_intersection(fromPoint, V, t_min, t_max);
        if (is == nullptr) {
            continue;
        }
        intersections.emplace_back(object, *is);
    }
    if (intersections.empty()) {
        return boost::none;
    }
    pair<obj_sp, intersection> *nearest = intersections.begin().base();
    float d_min = nearest->second.distance;
    for (auto &item : intersections) {
        float d = item.second.distance;
        if (d < d_min) {
            nearest = &item;
            d_min = d;
        }
    }
    return *nearest;
}

bool scene::any_collision(const vec3f &fromPoint, const vec3f &V, float t_min, float t_max) const {
    for (const auto &sphere : objects) {
        intersection*p = sphere->ray_intersection(fromPoint, V, t_min, t_max);
        if (p != nullptr) {
            delete p;
            return true;
        }
    }
    return false;
}




