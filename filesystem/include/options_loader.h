

#ifndef GLASSYRENDER_OPTIONS_LOADER_H
#define GLASSYRENDER_OPTIONS_LOADER_H

using std::string;

class options_loader {
public:
    static void load(const string &str) {
        if (str.empty()) {
            throw std::invalid_argument("Path cannot be empty");
        }
        auto p = "path";
//                path(str).string();
        try {
            const YAML::Node node = YAML::LoadFile(str);
            auto &opts = render_options::get_instance();
            if (node["ambient_light"].IsDefined()) {
                opts.ambient_light = node["ambient_light"].as<float>();
            }
            if (node["camera_exposure"].IsDefined()) {
                opts.camera_exposure = node["camera_exposure"].as<float>();
            }
            if (node["gamma"].IsDefined()) {
                opts.gamma = node["gamma"].as<float>();
            }
            if (node["width"].IsDefined()) {
                opts.width = node["width"].as<int>();
            }
            if (node["height"].IsDefined()) {
                opts.height = node["height"].as<int>();
            }
            if (node["FOV"].IsDefined()) {
                opts.FOV = node["FOV"].as<float>();
            }
        } catch (std::exception &e) {
            string str = "Error while loading settings. Details:\n\t";
            str += e.what();
            throw std::runtime_error(str);
        }
    }
};

#endif //GLASSYRENDER_OPTIONS_LOADER_H
