

#ifndef GLASSYRENDER_SCENE_LOADER_H
#define GLASSYRENDER_SCENE_LOADER_H

using std::string;
using std::filesystem::path;

#include <yaml-cpp/yaml.h>
#include <basic_image.h>
#include <texture.h>
#include "tga_utils.h"

class scene_loader {
public:

    static bool load(const string &str) {
        if (str.empty()) {
            throw std::invalid_argument(str);
        }
        const YAML::Node node = YAML::LoadFile(str);

        std::map<string, material_sp> materials;
        if (node["materials"].IsDefined()) {
            load_materials(node["materials"], materials);
            scene::get_instance().objects = std::move(load_objects(node["objects"], materials));
        }
    }

private:
    static objects_arr
    load_objects(const YAML::Node &nodes, std::map<string, material_sp> &map) {
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
                string path = node["path"].as<string>();
                obj = std::move(obj_file_handler::load(path));
                obj->set_material(mat);
            }
            objects.emplace_back(move(obj));
        }
        return objects;
    }

    static void
    load_materials(const YAML::Node &nodes, std::map<string, material_sp> &map) {
        for (auto &node : nodes) {
            auto name = node["name"].as<string>();
            auto albedo = parse_tex<vec3f>(node["albedo"]);
            auto normal = parse_tex<vec3f>(node["normal"]);
            auto rgh = parse_tex<float>(node["roughness"]);
            auto ao = parse_tex<float>(node["ao"]);
            auto mat = std::make_shared<material>(albedo, rgh, ao, normal);
            map[name] = mat;
        }
    }

    template<typename T>
    static shared_ptr<i_texture<T>> parse_tex(const YAML::Node &node) {
        auto type = node["type"].as<string>();
        if (type == "uniform") {
            T value = node["value"].as<T>();
            auto sp = std::make_shared<uniform_texture<T>>(value);
            return sp;
        } else {
            string path = node["path"].as<string>();
            basic_image<T> img = tga_utils<T>::load(path);
            auto sp = std::make_shared<basic_texture<T>>(std::move(img));
            return sp;
        }
    }
};

namespace YAML {
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
