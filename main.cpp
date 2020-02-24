
#include <vector>
#include <iostream>

#include <render.h>
#include <objects/polygonal_object.h>
#include <objects/obj_file_handler.h>
#include <command_handler.h>

using std::unique_ptr;
using std::vector;
using std::string;
using std::cin;
using std::cout;

void initialize_scene(objects_arr &spheres);

void initialize_scene2(objects_arr &spheres);

void initialize_scene3(objects_arr &spheres);

int main() {
    scene & _scene = scene::get_instance();
    render &r = render::get_instance();
    auto &lights = _scene.lights;
    lights.emplace_back(new vector_light_source{
            5.0f, vec3f{1, 1, 1}, vec3f{0, -1, 1}});
    lights.emplace_back(new point_light_source{
            5.0f, vec3f{1, 0.8f, 0.5f}, vec3f{10, 0, -20}});
    affine_transform at = {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, -1,
            0, 0, 0, 1
    };
    render::get_instance().move_cam(at);
    auto &spheres = scene::get_instance().objects;
    initialize_scene(spheres);

    command_handler *handler = new command_handler(std::cout, std::cin);
    handler->loop();
}

void initialize_scene3(vector<i_object *> &scene) {
//    obj_file_handler obj;
//    std::string path(R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\guitar\Guitar.obj)");
//    scene.emplace(obj.load(path)->begin());
//    vec3f_arr *v = new vec3f_arr();
//    vec3f_arr *vn = new vec3f_arr();
//    vector<vec2f> *vt = new vector<vec2f>();
//    vector<face> *faces = new vector<face>();
//    v->emplace_back(
//            vec3f{0, 0, 0}
//    );
//    v->emplace_back(
//            vec3f{0, 1, 0}
//    );
//    v->emplace_back(
//            vec3f{1, 1, 0}
//    );
//    v->emplace_back(
//            vec3f{1, 0, 1}
//    );
//    vt->push_back(
//            vec2f{0, 0});
//    vt->push_back(
//            vec2f{0, 1});
//    vt->push_back(
//            vec2f{1, 1});
//    vt->push_back(
//            vec2f{1, 0});
//    vn->push_back(
//            vec3f{1, 1, 1}.normalized_copy()
//    );
//
//    faces->push_back(
//            face{
//                    vec3i{1, 2, 4},
//                    vec3i{1, 2, 4},
//                    vec3i{1, 1, 1}
//            });
//    faces->push_back(
//            face{
//                    vec3i{3, 2, 4},
//                    vec3i{3, 2, 4},
//                    vec3i{1, 1, 1}
//            });
//    std::string path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_col.tga)";
//    i_rgb_texture *albedo = new mapped_rgb_texture(path, true, 2.2f);
//    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_AO.tga)";
//    i_monochrome_texture *ao = new mapped_monochrome_texture(path);
//
//    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_nrm.tga)";
//    i_rgb_texture *normal = new mapped_rgb_texture(path);
//
//    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_rgh.tga)";
//    i_monochrome_texture *rgh = new mapped_monochrome_texture(path);
//    affine_transform at = affine_transform_factory::move(vec3f{0, 0, 0});
//    scene.push_back(
//            new polygonal_object(
//                    albedo,
//                    rgh,
//                    normal,
//                    ao,
//                    v,
//                    vt,
//                    vn,
//                    faces)
//    );
}

void initialize_scene2(objects_arr &spheres) {
    using std::make_shared;
    std::string path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_col.tga)";
    auto albedo = mapped_texture_rgb::load(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_AO.tga)";
    auto ao = mapped_texture_mono::load(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_nrm.tga)";
    auto normal = mapped_texture_rgb::load(path, true, 2.2f);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_rgh.tga)";
    auto rgh = mapped_texture_mono::load(path, true, 2.2f);

    material_sp mat = std::make_shared<material>(albedo, rgh, ao, normal);

    affine_transform at = affine_transform_factory::move(vec3f{-6 , 0, 0});

    auto *s = new sphere(6.0f, mat);
    s->apply(at);
    spheres.emplace_back(s);

    auto at2 = affine_transform_factory::move(vec3f{6, 0, 0});

    auto *s2 = new sphere(6.0f, mat);
    s2->apply(at2);
    spheres.emplace_back(s2);
}

void initialize_scene(objects_arr &spheres) {
    std::string path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_col.tga)";
    auto albedo = mapped_texture_rgb::load(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_AO.tga)";
    auto ao = mapped_texture_mono::load(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_nrm.tga)";
    auto normal = mapped_texture_rgb::load(path, true, 2.2f);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\[2K]PavingStones36\PavingStones36_rgh.tga)";
    auto rgh = mapped_texture_mono::load(path, true, 2.2f);

    material_sp mat = std::make_shared<material>(albedo, rgh, ao, normal);
    auto obj = obj_file_handler::load(R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\cube.obj)");
    obj->set_material(mat);
    obj->apply(affine_transform_factory::stretch(vec3f{1.1f, 0.7f, 0.7}));
    obj->apply(affine_transform_factory::rotateZ(30, {0, 0, 0}));
    obj->apply(affine_transform_factory::rotateX(30, {0, 0, 0}));
    obj->apply(affine_transform_factory::move({-0.1f, 0.05f, 0.2f}));
    spheres.push_back(obj);
    auto *s2 = new sphere(0.2f, mat);
    spheres.emplace_back(s2);
}
