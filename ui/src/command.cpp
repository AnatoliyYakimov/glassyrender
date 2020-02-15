

#include <command.h>

#include <memory>

unique_ptr<commands> command::registry = std::make_unique<commands>();


bool exit_command::_static_init() {
    command::registry->push_back(new exit_command("exit"));
    return false;
}

bool exit_command::_init = exit_command::_static_init();


bool render_command::_static_init() {
    return false;
}

