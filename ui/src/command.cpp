

#include <command.h>

#include <memory>

unique_ptr<commands> command::registry = std::make_unique<commands>();

void exit_command::exec(const vector<string> &args, const ostream &os) {
    throw runtime_error("Exit");
}



bool exit_command::_static_init() {
    command::registry->push_back(new exit_command("exit"));
    return false;
}

bool exit_command::_init = exit_command::_static_init();

exit_command::exit_command(const string &signature) : command(signature) {}
