//
// Created by Yakimov on 30.09.2019.
//

#ifndef GLASSYRENDER_VIEWPORT_H
#define GLASSYRENDER_VIEWPORT_H


#include <functional>
#include "../Entities/vec.h"

class viewport {
public:
    point3f O;
    point3f Ow;
    float d = 1;
    float Px;
    float Py;
    int Height;
    int Width;

    viewport(int, int);

    void recompute_size(int, int);

    auto transformer_function();
};

auto viewport::transformer_function() {
    return [this](int u, int v) -> vec3f {
        auto &t = *this;
        return
                vec3f(O, point3f{
                        (static_cast<float>(u) - t.Ow[0])/Ow[0],
                        (static_cast<float>(v) - t.Ow[1])/Ow[0],
                        1.4f

                });
    };
}

viewport::viewport(const int W, const int H)
        : Height(H),
          Width(W),
          O(point3f{0, 0, 0}),
          Ow(point3f{
                  static_cast<float>(W) * 0.5f,
                  static_cast<float>(H) * 0.5f,
                  200.0f
          }),
          d(Ow[2] - O[2]),
          Px(10),
          Py(10) {
}

void viewport::recompute_size(int W, int H) {
    Ow[0] = static_cast<float>(W) * 0.5f;
    Ow[1] = static_cast<float>(H) * 0.5f;
}


#endif //GLASSYRENDER_VIEWPORT_H
