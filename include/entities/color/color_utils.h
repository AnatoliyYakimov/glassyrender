//
// Created by Yakimov on 30.11.2019.
//

#ifndef GLASSYRENDER_COLOR_UTILS_H
#define GLASSYRENDER_COLOR_UTILS_H

#include <wingdi.h>
#include "../algebra/vec.h"

class color_utils {
private:
    static const int r_pos = 0xF00;
    static const int g_pos = 0xF0;
    static const int b_pos = 0xF;
public:
    static inline vec3f rgb(const COLORREF col) {
        return vec3f{ GetRValue(col) / 255.0f, GetGValue(col) / 255.0f, GetBValue(col) / 255.0f };
    }

    static inline COLORREF colorref(const vec3f& rgb) {
        return RGB(rgb[0] * 255, rgb[1] * 255, rgb[2] * 255);
    }

};

#endif //GLASSYRENDER_COLOR_UTILS_H
