//
// Created by Yakimov on 02.11.2019.
//

#ifndef GLASSYRENDER_RGB_H
#define GLASSYRENDER_RGB_H


#include <cassert>
#include <windef.h>
#include <wingdi.h>
#include "../algebra/vec.h"

class sRGB {
private:
    float values[3];
public:
    sRGB() : sRGB(1){};
    sRGB(const sRGB& rgb);
    sRGB(const vec3f& v) : sRGB(v[0], v[1], v[2]){};
    explicit sRGB(float r, float g, float b);
    explicit sRGB(float col) : sRGB(col, col, col) {};

    sRGB mix(sRGB rgb) {
        for (size_t i = 3; i--;) {
            rgb[i] *= values[i];
        }
        return rgb;
    }

    COLORREF colorref() const {
        return RGB(values[0], values[1], values[2]);
    }

    const float& operator[](unsigned int idx) const {
        assert(idx < 3);
        return values[idx];
    }

    float& operator[](unsigned int idx) {
        assert(idx < 3);
        return values[idx];
    }

    sRGB operator-() {
        sRGB res = sRGB(*this);
        for (size_t i = 3; i--;) {
            res[i] *= -1;
        }
        return res;
    }

    friend sRGB operator*(float a, const sRGB rhs);
    friend sRGB operator*(sRGB lhs, float a);
    friend sRGB operator/(sRGB lhs, float a);
    friend sRGB operator+(sRGB lhs, const sRGB &rhs);
    friend sRGB operator-(sRGB lhs, const sRGB &rhs);
};


#endif //GLASSYRENDER_RGB_H
