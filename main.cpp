
#include <vector>
#include <iostream>

#include <render.h>
#include <objects/polygonal_object.h>
#include <objects/obj_file_handler.h>
#include <command_handler.h>
#include <scene_loader.h>
#include <tga_utils.h>

using std::unique_ptr;
using std::vector;
using std::string;
using std::cin;
using std::cout;

void initialize_scene(objects_arr &spheres);


int main() {
    string resources = "resources/";
    try {
        scene_loader::load(resources + "scene.yaml");
        cout << "Scene autoloaded successfully";
    } catch (std::exception &e) {
        cout << "Scene autoload fail";
    }
    cout << std::endl;
    try {
        options_loader::load(resources + "options.yaml");
        cout << "Options autoloaded successfully";
    } catch (std::exception &e) {
        cout << "Options autoload fail";
    }

    command_handler *handler = new command_handler(std::cout, std::cin);
    handler->loop();
}

void initialize_scene(objects_arr &spheres) {
    std::string path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\PavingStones\PavingStones36_col.tga)";
    auto albedo = tga_utils<vec3f>::load(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\PavingStones\PavingStones36_AO.tga)";
    auto ao = tga_utils<float>::load(path, true, 2.2f);
    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\PavingStones\PavingStones36_nrm.tga)";
    auto normal =tga_utils<vec3f>::load(path, true, 2.2f);

    path = R"(C:\Users\Yakimov\CLionProjects\GlassyRender\resources\PavingStones\PavingStones36_rgh.tga)";
    auto rgh = tga_utils<float>::load(path, true, 2.2f);

    auto a_sp = std::make_shared<mapped_texture_rgb>(std::move(albedo));
    auto n_sp = std::make_shared<mapped_texture_rgb>(std::move(normal));
    auto rgh_sp = std::make_shared<mapped_texture_mono>(std::move(rgh));
    auto ao_sp = std::make_shared<mapped_texture_mono>(std::move(ao));

    material_sp mat = std::make_shared<material>(a_sp, rgh_sp, ao_sp, n_sp);
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
