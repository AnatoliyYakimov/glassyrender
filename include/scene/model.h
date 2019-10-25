//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_MODEL_H
#define GLASSYRENDER_MODEL_H

#include <vector>
#include "../entities/sphere.h"
#include "../../Constants.h"
#include "../entities/i_light_source.h"

class model {
public:
    explicit model(ARRAY_LIST<sphere> &spheres);
    model() = default;

    [[nodiscard]] const ARRAY_LIST<sphere> &getSpheres() const;

    void setSpheres(const ARRAY_LIST<sphere> &spheres);

    const std::vector<i_light_source *> &getLights() const;

    void setLights(const std::vector<i_light_source *> &lights);

private:
    ARRAY_LIST<sphere> spheres;
    ARRAY_LIST<i_light_source*> lights;
};


#endif //GLASSYRENDER_MODEL_H
