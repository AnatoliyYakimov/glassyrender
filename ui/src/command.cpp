

#include <command.h>

#include <memory>

unique_ptr<commands> command::registry = std::make_unique<commands>();


bool exit_command::_static_init() noexcept {
    command::registry->push_back(new exit_command("exit"));
    return false;
}

bool exit_command::_init = exit_command::_static_init();


bool render_command::_static_init() noexcept {
    command::registry->push_back(new render_command("render"));
    return false;
}

bool render_command::_init = render_command::_static_init();

bool load_scene_command::_static_init() noexcept {
    command::registry->push_back(new load_scene_command("scene"));
    return false;
}

bool load_scene_command::_init = load_scene_command::_static_init();
