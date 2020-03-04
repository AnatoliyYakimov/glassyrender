

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
#include <options_loader.h>

using std::string;
using std::vector;
using std::unique_ptr;
using std::ostream;
using std::istream;
using std::exception;

class command {
protected:
    const string signature = "";

    explicit command(string signature) : signature(std::move(signature)) {};

protected:
    void few_arguments(ostream &os, const string &expected = "") {
        os << "Too few arguments";
        if (!expected.empty()) {
            os << "\nExpected: " << expected;
        }
        os.flush();
    }

    void invalid_argument(ostream &os,
                          const string &argument,
                          const string &expected = "") {
        os << "Invalid argument \"" << argument << "\"\n";
        if (!expected.empty()) {
            os << "Expected: " << expected;
        }
        os.flush();
    }

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
        auto it = ++args.begin();
        std::filesystem::path path(*it);
        if (path.empty()) {
            path.assign(".");
        }
        string file_name = "test";
        if (++it != args.end()) {
            file_name = *it;
        }

        auto path_str = (path / (file_name + ".png")).string();
        auto img = render::get_instance().render_image();
        auto png = png_utils::to_16bit(img);
        try {
            png->write(path_str);
        } catch (exception &e) {
            std::stringstream str;
            str << "Error while saving image. Details:\n\t" << e.what();
            throw std::runtime_error(str.str());
        }
        os << "Rendering done. Result saved as \"" << path_str << "\"";
        os.flush();
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
            few_arguments(os, R"("load" or "clear")");
            return;
        }
        auto it = ++args.begin();
        if (*it == "clear") {
            scene::get_instance().objects.clear();
            scene::get_instance().lights.clear();
            os << "Scene cleared successfully";
        } else if (*it == "load") {
            if (++it == args.end()) {
                few_arguments(os, "path to .yaml file");
                return;
            }
            const string &file_path = *it;
            scene_loader::load(file_path);
            os << "Scene loaded successfully";
        } else {
            invalid_argument(os, *it, R"("load" or "clear")");
        }
    }
};

class load_options_command : public command {
private:
    static bool _init;

    static bool _static_init() noexcept;

    explicit load_options_command(const string &signature) : command(signature) {}

public:

    void exec(const vector<string> &args, ostream &os) override {
        if (args.size() < 2) {
            few_arguments(os, R"(path to .yaml file)");
            return;
        }
        auto it = ++args.begin();
        options_loader::load(*it);
        os << "Options loaded successfully";
    }
};

#endif //GLASSYRENDER_COMMAND_H
