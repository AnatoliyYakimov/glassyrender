

#ifndef GLASSYRENDER_RENDER_OPTIONS_H
#define GLASSYRENDER_RENDER_OPTIONS_H

class render_options : public singleton {
public:
    static render_options &get_instance() {
        static render_options s;
        return s;
    }
    float ambient_light = 0.2f;
    float gamma = 2.2;
    float camera_exposure = 1;
    int width = 1280;
    int height = 720;
    float FOV = 1.2f;
};

#endif //GLASSYRENDER_RENDER_OPTIONS_H
