

#ifndef GLASSYRENDER_COMMAND_H
#define GLASSYRENDER_COMMAND_H

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <basic_image.h>
#include <render.h>
#include <png_utils.h>
#include <image.hpp>
#include <scene_loader.h>

using std::string;
using std::vector;
using std::unique_ptr;
using std::ostream;
using std::istream;

class command {
protected:
    const string signature = "";

    explicit command(string signature) : signature(std::move(signature)) {};

public:
    static unique_ptr<vector<command *>> registry;

    bool is_signature(const string &str) {
        return signature == str;
    }

    virtual void exec(const vector<string> &args, ostream &os) = 0;

    virtual ~command() = default;
};

typedef vector<command *> commands;

class exit_command : private command {
private:
    static bool _init;

    static bool _static_init() noexcept;

    explicit exit_command(const string &signature) : command(signature) {}

public:

    void exec(const vector<string> &args, ostream &os) override {
        std::exit(0);
    }
};

class render_command : private command {
private:
    static bool _init;

    static bool _static_init() noexcept;

    explicit render_command(const string &signature) : command(signature) {}

public:

    void exec(const vector<string> &args, ostream &os) override {
        if (args.size() < 2) {
            throw std::runtime_error("Too few arguments fro command");
        }
        auto it = ++args.begin();
        const string &file_path = *it;
        string file_name = "test";
        if (++it != args.end()) {
            file_name = *it;

        }
        std::filesystem::path path(file_path);
        if (path.empty()) {
            path.assign(".");
        }
        png::image<png::rgb_pixel_16> *png = nullptr;
        try {
            auto img = render::get_instance().render_image();
            png = png_utils::to_16bit(img);
            png->write(file_name + ".png");
            os << "Done!";
            os.flush();
        } catch (std::exception &e) {
            delete png;
            throw e;
        }
        delete png;
    }

    ~render_command() override = default;
};

class load_scene_command : public command {
private:
    static bool _init;

    static bool _static_init() noexcept;

    explicit load_scene_command(const string &signature) : command(signature) {}

public:

    void exec(const vector<string> &args, ostream &os) override {
        if (args.size() < 2) {
            throw std::runtime_error("Too few arguments fro command");
        }
        auto it = ++args.begin();
        const string &file_path = *it;
        scene_loader::load(file_path);
        os << "Done!";
        os.flush();

    }
};

#endif //GLASSYRENDER_COMMAND_H
