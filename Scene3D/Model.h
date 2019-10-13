//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_MODEL_H
#define GLASSYRENDER_MODEL_H

#include <vector>
#include "../Entities/sphere.h"
#include "../Constants.h"

class Model {
public:
    explicit Model(ARRAY_LIST<Sphere> &spheres);
    Model() = default;

    [[nodiscard]] const ARRAY_LIST<Sphere> &getSpheres() const;

    void setSpheres(const ARRAY_LIST<Sphere> &spheres);
private:
    ARRAY_LIST<Sphere> spheres;
};


#endif //GLASSYRENDER_MODEL_H
