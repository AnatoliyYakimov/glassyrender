//
// Created by Yakimov on 25.10.2019.
//


#include <viewport.h>

void viewport::recompute_size(int width, int height) {
    divider = 1.0f / (float)(width > height ? width : height);
}

void viewport::apply(const affine_transform &at) {
    to_world = at * to_world;
    Vx = ((at * Vx.extend(0)).shrink()).normalize();
    Vy = ((at * Vy.extend(0)).shrink()).normalize();
    origin_pos = at * origin_pos;
    camera_pos = origin_pos - FOV * vector_utils<float>::vector_product(Vx,
                                                                      Vy).normalize();
}

