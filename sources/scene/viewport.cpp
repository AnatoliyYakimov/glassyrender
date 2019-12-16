//
// Created by Yakimov on 25.10.2019.
//


#include "../../include/scene/viewport.h"


viewport::viewport(const int W, const int H, const float d)
        : width(W),
          height(H),
          camera_pos({0, 0, -d}),
          origin_pos({0,0,0}),
          to_world(affine_transform::identity()),
          d(d) {
    recompute_size(H, W);
}

void viewport::recompute_size(int H, int W) {
    height = H;
    width = W;
    divider = 1.0f / ((width > height ? width : height));
}

void viewport::apply(const affine_transform &at) {
    to_world = at * to_world;
    Vx = ((at * Vx.extend(0)).shrink()).normalize();
    Vy = ((at * Vy.extend(0)).shrink()).normalize();
    origin_pos = at * origin_pos;
    camera_pos = origin_pos - d * vector_utils<float>::vector_product(Vx,
                                                                      Vy).normalize();
}

