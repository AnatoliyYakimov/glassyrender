

#ifndef GLASSYRENDER_SCENE_LOADER_H
#define GLASSYRENDER_SCENE_LOADER_H

using std::string;
using std::filesystem::path;

#include <yaml-cpp/yaml.h>
#include <basic_image.h>
#include <texture.h>
#include <objects/obj_file_handler.h>
#include <tga_utils.h>

using std::filesystem::path;

class scene_loader {
public:

    static void load(const string &str) {
        if (str.empty()) {
            throw std::invalid_argument(str);
        }
        auto p = path(str).string();
        const YAML::Node node = YAML::LoadFile(str);

        std::map<string, material_sp> materials;
        std::map<string, affine_transform> transforms;
        auto prefix = std::filesystem::path(str).parent_path().string() + "\\";

        if (node["materials"].IsDefined()) {
            load_materials(node["materials"], materials, prefix);
            scene::get_instance().objects = std::move(load_objects(node["objects"], materials, prefix));
        }
    }

private:
    static affine_transform load_transform(const YAML::Node &nodes) {
        affine_transform tr = affine_transform::identity();
        for (auto &node : nodes) {
            tr = tr * node.as<affine_transform>();
        }
        return tr;
    }


    static objects_arr
    load_objects(const YAML::Node &nodes, std::map<string, material_sp> &map, const string &prefix) {
        objects_arr objects;
        obj_sp obj = obj_sp(nullptr);
        for (auto &node : nodes) {
            auto type = node["type"].as<string>();
            auto mat_name = node["material"]["name"].as<string>();
            material_sp mat = map[mat_name];
            if (type == "sphere") {
                float radius = node["radius"].as<float>();
                obj.reset(new sphere(radius, mat));
            } else if (type == "polygonal") {
                string path_str = get_path(node["path"].as<string>(), prefix);
                obj = std::move(obj_file_handler::load(path_str));
                obj->set_material(mat);
            }
            affine_transform transform = load_transform(node["transform"]);
            obj->apply(transform);
            objects.emplace_back(move(obj));
        }
        return objects;
    }

    static void
    load_materials(const YAML::Node &nodes, std::map<string, material_sp> &map, const string &prefix) {
        for (auto &node : nodes) {
            auto name = node["name"].as<string>();
            auto albedo = parse_tex<vec3f>(node["albedo"], prefix);
            auto normal = parse_tex<vec3f>(node["normal"], prefix);
            auto rgh = parse_tex<float>(node["roughness"], prefix);
            auto ao = parse_tex<float>(node["ao"], prefix);
            auto mat = std::make_shared<material>(albedo, rgh, ao, normal);
            map[name] = mat;
        }
    }

    template<typename T>
    static shared_ptr<i_texture<T>> parse_tex(const YAML::Node &node, const string &prefix) {
        auto type = node["type"].as<string>();
        if (type == "uniform") {
            T value = node["value"].as<T>();
            auto sp = std::make_shared<uniform_texture<T>>(value);
            return sp;
        } else {
            string path_str = get_path(node["path"].as<string>(), prefix);
            basic_image<T> img = tga_utils<T>::load(path_str);
            auto sp = std::make_shared<basic_texture<T>>(std::move(img));
            return sp;
        }
    }

    static string get_path(const string &str, const string &prefix) {
        auto p = path(str);
        string path_str;
        if (p.is_relative()) {
            path_str = prefix + p.string();
        } else {
            path_str = p.string();
        }
        return path_str;
    }
};

namespace YAML {
    template<>
    struct convert<affine_transform> {
         Node encode(const affine_transform& rhs) {
            Node node;
            return node;
        }

        static bool decode(const Node& node, affine_transform& rhs) {
            string type = node["type"].as<string>();
            if (type == "rotate") {
                auto angle = node["angle"].as<float>();
                vec3f point = vec3f{0, 0, 0};
                if (node["point"].IsDefined()) {
                    point = node["point"].as<vec3f>();
                }
                auto axis = node["axis"].as<char>();
                switch (axis) {
                    case 'x':
                        rhs = affine_transform_factory::rotateX(angle, point);
                        break;
                    case 'y':
                        rhs = affine_transform_factory::rotateY(angle, point);
                        break;
                    case 'z':
                        rhs = affine_transform_factory::rotateZ(angle, point);
                        break;
                }
            } else if (type == "stretch") {
                auto arg = node["arg"].as<vec3f>();
                rhs = affine_transform_factory::stretch(arg);
            } else if (type == "move") {
                auto point = node["point"].as<vec3f>();
                rhs = affine_transform_factory::move(point);
            } else {
                return false;
            }
            return true;
        }
    };

    template<>
    struct convert<vec3f> {
        static Node encode(const vec3f& rhs) {
            Node node;
            node.push_back(rhs[0]);
            node.push_back(rhs[1]);
            node.push_back(rhs[2]);
            return node;
        }

        static bool decode(const Node& node, vec3f& rhs) {
            if(!node.IsSequence() || node.size() != 3) {
                return false;
            }

            rhs[0] = node[0].as<float>();
            rhs[1] = node[1].as<float>();
            rhs[2] = node[2].as<float>();
            return true;
        }
    };
}

#endif //GLASSYRENDER_SCENE_LOADER_H
