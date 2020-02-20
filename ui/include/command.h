

#ifndef GLASSYRENDER_COMMAND_H
#define GLASSYRENDER_COMMAND_H

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <cli_exception.h>
#include <filesystem>
#include <abstract_image.h>
#include <image.hpp>
#include <render.h>

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
            throw cli_exception(cli_exception::error_code::INVALID_ARGS);
        }
        auto it = args.begin()++;
        const string &file_path = *it;
        string file_name = "test.png";
        if (++it != args.end()){
            file_name = *it;

        }
        std::filesystem::path path(file_path);
        if (path.empty()) {
            path.assign(".");
        }
        try {
            abstract_image img = render::get_instance().render_image();
            png::image<png::rgb_pixel_16>* png = img.to_png16();
            png->write("test.png");
            os << "Done!";
            os.flush();
            delete png;
        } catch (exception &e) {
            throw cli_exception(cli_exception::OTHER, e);
        }


    }

    ~render_command() override = default;
};

#endif //GLASSYRENDER_COMMAND_H
