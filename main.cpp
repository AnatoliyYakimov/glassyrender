
#include <vector>
#include <iostream>

#include <render.h>
#include <objects/polygonal_object.h>
#include <obj_file_handler.h>
#include <command_handler.h>

using std::unique_ptr;
using std::vector;
using std::string;
using std::cin;
using std::cout;

void initialize_scene(std::vector<i_object *> &spheres);

void initialize_scene2(unique_ptr<vector<i_object *>> &spheres);

void initialize_scene3(vector<i_object *> &scene);

int main() {
    scene & _scene = scene::get_instance();
    render &r = render::get_instance();
    auto &lights = _scene.lights;
    lights->push_back(new vector_light_source{
            2.0f, vec3f{1, 1, 1}, vec3f{5, -5, 5}});
    lights->push_back(new point_light_source{
            10.0f, vec3f{1, 0, 0}, vec3f{1, 1, -1}});
    affine_transform at = {
            1, 0, 0, 1,
            0, 1, 0, -4,
            0, 0, 1, -50,
            0, 0, 0, 1
    };
    render::get_instance().move_cam(at);
    auto &spheres = scene::get_instance().objects;
    initialize_scene2(spheres);

    command_handler *handler = new command_handler(std::cout, std::cin);
    handler->loop();
}

void initialize_scene3(vector<i_object *> &scene) {
//    obj_file_handler obj;
//    std::string path(R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\guitar\Guitar.obj)");
//    scene.emplace(obj.load(path)->begin());
    vec3f_arr *v = new vec3f_arr();
    vec3f_arr *vn = new vec3f_arr();
    vector<vec2f> *vt = new vector<vec2f>();
    vector<face> *faces = new vector<face>();
    v->emplace_back(
            vec3f{0, 0, 0}
    );
    v->emplace_back(
            vec3f{0, 1, 0}
    );
    v->emplace_back(
            vec3f{1, 1, 0}
    );
    v->emplace_back(
            vec3f{1, 0, 1}
    );
    vt->push_back(
            vec2f{0, 0});
    vt->push_back(
            vec2f{0, 1});
    vt->push_back(
            vec2f{1, 1});
    vt->push_back(
            vec2f{1, 0});
    vn->push_back(
            vec3f{1, 1, 1}.normalized_copy()
    );

    faces->push_back(
            face{
                    vec3i{1, 2, 4},
                    vec3i{1, 2, 4},
                    vec3i{1, 1, 1}
            });
    faces->push_back(
            face{
                    vec3i{3, 2, 4},
                    vec3i{3, 2, 4},
                    vec3i{1, 1, 1}
            });
    std::string path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_col.tga)";
    i_rgb_texture *albedo = new mapped_rgb_texture(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_AO.tga)";
    i_monochrome_texture *ao = new mapped_monochrome_texture(path);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_nrm.tga)";
    i_rgb_texture *normal = new mapped_rgb_texture(path);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_rgh.tga)";
    i_monochrome_texture *rgh = new mapped_monochrome_texture(path);
    affine_transform at = affine_transform_factory::move(vec3f{0, 0, 0});
    scene.push_back(
            new polygonal_object(
                    albedo,
                    rgh,
                    normal,
                    ao,
                    v,
                    vt,
                    vn,
                    faces)
    );
}

void initialize_scene2(unique_ptr<vector<i_object *>> &spheres) {
    std::string path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_col.tga)";
    i_rgb_texture *albedo = new mapped_rgb_texture(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_AO.tga)";
    i_monochrome_texture *ao = new mapped_monochrome_texture(path);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_nrm.tga)";
    i_rgb_texture *normal = new mapped_rgb_texture(path);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_rgh.tga)";
    i_monochrome_texture *rgh = new mapped_monochrome_texture(path);
    affine_transform at = affine_transform_factory::move(vec3f{0, 0, 0});

    sphere *s1 = new sphere(12.0f, albedo, rgh, normal, ao);
    s1->apply(at);
    spheres->push_back(s1);
}
