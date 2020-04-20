//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_SCENE_H
#define GLASSYRENDER_SCENE_H

#include <vector>
#include <constants.h>
#include <objects/i_object.h>
#include <objects/light.h>
#include <singleton.h>
#include <optional>

using std::shared_ptr;
using std::pair;
using std::optional;

typedef std::vector<obj_sp> objects_arr;
typedef std::vector<light_sp> lights_arr;

class scene : public singleton {
public:
    static scene &get_instance();

    objects_arr objects;
    lights_arr lights;

    vec3f scene_color = vec3f(1);

    [[nodiscard]] optional<pair<obj_sp, intersection>> nearest_collision(
            const vec3f &fromPoint, const vec3f &V,
            float t_min, float t_max) const;
    [[nodiscard]] bool any_collision(const vec3f &fromPoint, const vec3f &V,
                       float t_min, float t_max) const;

private:
    static scene *instance;
    scene() : objects(), lights() {}

};


#endif //GLASSYRENDER_SCENE_H
