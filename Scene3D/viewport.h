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
    float d = 1.4;
    float Px;
    float Py;
    int Height;
    int Width;

    viewport(int, int, float);

    void recompute_size(int, int);

    auto transformer_function();
};

auto viewport::transformer_function() {
    return [this](int u, int v) -> vec3f {
        return
                vec3f(O, point3f{
                        (static_cast<float>(u) - Ow[0])/Ow[0],
                        -(static_cast<float>(v) - Ow[1])/Ow[0],
                        d
                });
    };
}

viewport::viewport(const int W, const int H, const float d)
        : Height(H),
          Width(W),
          O(point3f{0, 0, 0}),
          Ow(point3f{
                  static_cast<float>(W) * 0.5f,
                  static_cast<float>(H) * 0.5f,
                  d
          }),
          d(d){}

void viewport::recompute_size(int H, int W) {
    Height = H;
    Width = W;
    Ow[0] = static_cast<float>(W) * 0.5f;
    Ow[1] = static_cast<float>(H) * 0.5f;
}


#endif //GLASSYRENDER_VIEWPORT_H
