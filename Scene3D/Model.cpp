//
// Created by Yakimov on 30.09.2019.
//

#include "Model.h"


const ARRAY_LIST<Sphere> &Model::getSpheres() const {
    return spheres;
}

void Model::setSpheres(const ARRAY_LIST<Sphere> &spheres) {
    Model::spheres = spheres;
}

Model::Model(ARRAY_LIST<Sphere> &spheres) : spheres(spheres) {
}
