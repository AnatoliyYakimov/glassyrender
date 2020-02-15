

#ifndef GLASSYRENDER_COMMAND_H
#define GLASSYRENDER_COMMAND_H

#include <utility>
#include <vector>
#include <string>
#include <memory>
#include <cli_exception.h>
#include <filesystem>

using namespace std;


class command {
protected:
    const string signature = "";

    explicit command(const string &signature) : signature(signature) {};

public:
    static unique_ptr<vector<command *>> registry;

    bool is_signature(const string &str) {
        return signature == str;
    }

    virtual void exec(const vector<string> &args, const ostream &os) = 0;

    virtual ~command() {}
};

typedef vector<command *> commands;

class exit_command : private command {
private:
    static bool _init;

    static bool _static_init();

    explicit exit_command(const string &signature) : command(signature) {}
public:

    void exec(const vector<string> &args, const ostream &os) override {
        throw cli_exception(cli_exception::error_code::EXIT);
    }

    ~exit_command() override {}
};

class render_command : private command {
private:
    static bool _init;

    static bool _static_init();

    explicit render_command(const string &signature) : command(signature) {}
public:

    void exec(const vector<string> &args, const ostream &os) override {
        if (args.size() < 2) {
            throw cli_exception(cli_exception::error_code::INVALID_ARGS);
        }
        auto it = args.begin()++;
        const string &file_path = *it;
        filesystem::path path(file_path);
        if (!path.empty()) {
            throw cli_exception(cli_exception::error_code::INVALID_ARGS);
        }
        try {
            ifstream fs(path);

        }

    }

    ~render_command() override = default;
};

#endif //GLASSYRENDER_COMMAND_H
