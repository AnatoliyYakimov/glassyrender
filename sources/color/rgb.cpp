//
// Created by Yakimov on 02.11.2019.
//

#include "../../include/entities/color/rgb.h"

sRGB::sRGB(float r, float g, float b) : values() {
    values[0] = r;
    values[1] = g;
    values[2] = b;
}

sRGB::sRGB(const sRGB &rgb) : values() {
    for (int i = 0; i < 3; ++i) {
        values[i] = rgb[i];
    }
}

sRGB operator*(float a, sRGB rhs) {
    for (size_t i = 3; i--;) {
        rhs[i] *= a;
    }
    return rhs;
}

sRGB operator*(sRGB lhs, float a) {
    for (size_t i = 3; i--;) {
        lhs[i] *= a;
    }
    return lhs;
}

sRGB operator/(sRGB lhs, float a) {
    for (size_t i = 3; i--;) {
        lhs[i] /= a;
    }
    return lhs;
}

sRGB operator+(sRGB lhs, const sRGB &rhs) {
    for (size_t i = 3; i--;) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

sRGB operator-(sRGB lhs, const sRGB &rhs) {
    for (size_t i = 3; i--;) {
        lhs[i] -= rhs[i];
    }
    return lhs;
}
