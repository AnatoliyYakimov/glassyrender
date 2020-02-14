//
// Created by Yakimov on 01.12.2019.
//

#ifndef GLASSYRENDER_TEXTURE_MAP_LOADER_H
#define GLASSYRENDER_TEXTURE_MAP_LOADER_H


#include <vector>
#include <vec.h>
#include "tga.h"

class texture_map_loader {
public:
    static std::tuple<std::vector<vec3f>*, int, int> load_tga_rgb(const std::string &file_path, bool apply_gamma = false, float gamma = 1.0f);
    static std::tuple<std::vector<float>*, int, int>  load_tga_monochrome(const std::string &file_path, bool apply_gamma = false, float gamma = 1.0f);
};


#endif //GLASSYRENDER_TEXTURE_MAP_LOADER_H
