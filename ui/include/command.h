

#ifndef GLASSYRENDER_COMMAND_H
#define GLASSYRENDER_COMMAND_H

#include <utility>
#include <vector>
#include <string>
#include <memory>

using namespace std;


class command {
protected:
    const string signature = "";

    explicit command(const string &signature) : signature(signature) {};

public:
    static unique_ptr<vector<command*>> registry;

    bool is_signature(const string &str) {
        return signature == str;
    }
    virtual void exec(const vector<string> &args, const ostream &os) = 0;
    virtual ~command() {}
};
typedef vector<command*> commands;

class exit_command : private command {
private:
    static bool _init;
    static bool _static_init();

public:
    exit_command(const string &signature);

    void exec(const vector<string> &args, const ostream &os) override;

    ~exit_command() override {}
};
#endif //GLASSYRENDER_COMMAND_H
