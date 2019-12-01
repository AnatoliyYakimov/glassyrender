//
// Created by Yakimov on 09.11.2019.
//

#ifndef GLASSYRENDER_POLYGONAL_OBJECT_H
#define GLASSYRENDER_POLYGONAL_OBJECT_H

#include "i_object.h"

struct face {
    vec3f v;
    vec3f vt;
    vec3f n;
};

class polygonal_object : public i_object {
protected:
    std::vector<face> faces;
public:

};
#endif //GLASSYRENDER_POLYGONAL_OBJECT_H
