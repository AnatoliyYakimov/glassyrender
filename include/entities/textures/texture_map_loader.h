//
// Created by Yakimov on 01.12.2019.
//

#ifndef GLASSYRENDER_TEXTURE_MAP_LOADER_H
#define GLASSYRENDER_TEXTURE_MAP_LOADER_H


#include <vector>
#include "../algebra/vec.h"
#include "../../../lib/tga/tga.hpp"

class texture_map_loader {
public:
    static std::vector<vec3f>* load_tga(const tga::TGA& tga, bool apply_gamma = false, float gamma = 1.0f);

};


#endif //GLASSYRENDER_TEXTURE_MAP_LOADER_H
