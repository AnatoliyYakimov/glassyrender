

#ifndef GLASSYRENDER_MATERIAL_H
#define GLASSYRENDER_MATERIAL_H

#include <utility>
#include <memory>

#include <texture.h>

using std::shared_ptr;
using std::move;

class material {
public:

    material(shared_ptr<texture_rgb> albedo_map,
             shared_ptr<texture_mono> roughness_map,
             shared_ptr<texture_mono> ao_map,
             shared_ptr<texture_rgb> normal_map)
            : albedo(move(albedo_map)),
              roughness(move(roughness_map)),
              ao(move(ao_map)),
              normal(move(normal_map)) {
    }

    [[nodiscard]] const shared_ptr<texture_rgb> &get_albedo() const {
        return albedo;
    }

    [[nodiscard]] const shared_ptr<texture_mono> &get_roughness() const {
        return roughness;
    }

    [[nodiscard]] const shared_ptr<texture_mono> &get_ao() const {
        return ao;
    }

    [[nodiscard]] const shared_ptr<texture_rgb> &get_normal() const {
        return normal;
    }

private:
    shared_ptr<texture_rgb> albedo;
    shared_ptr<texture_mono> roughness;
    shared_ptr<texture_mono> ao;
    shared_ptr<texture_rgb> normal;
};

typedef std::shared_ptr<material> material_sp;

#endif //GLASSYRENDER_MATERIAL_H
