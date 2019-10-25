//
// Created by Yakimov on 30.09.2019.
//

#include <algorithm>
#include "../../include/scene/model.h"


const ARRAY_LIST<sphere> &model::getSpheres() const {
    return spheres;
}

void model::setSpheres(const ARRAY_LIST<sphere> &spheres) {
    model::spheres = spheres;
// TODO сортировка сфер по близости к камере
//    std::sort(model::spheres.begin(), model::spheres.end(),
//            [](const sphere &s1, const sphere &s2) -> int {
//        if (s1.O)
//    });
}

model::model(ARRAY_LIST<sphere> &spheres) : spheres(spheres) {
}

const std::vector<i_light_source *> &model::getLights() const {
    return lights;
}

void model::setLights(const std::vector<i_light_source *> &lights) {
    model::lights = lights;
}

