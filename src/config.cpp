#include "config.hpp"

#include "inih/cpp/INIReader.h"

int Config::load(const char *path) {
    const INIReader reader(path);

    if (reader.ParseError() < 0) {
        return -1;
    }

    this->no_scroll = reader.GetBoolean("Options", "NoScroll", false);
    this->no_menu_animation = reader.GetBoolean("Options", "NoMenuAnimation", false);
    this->no_intro = reader.GetBoolean("Options", "NoIntro", false);
    this->no_gamedata = reader.GetBoolean("Options", "NoGamedata", false);

    this->show_console = reader.GetBoolean("Options", "ShowConsole", false);

    return 0;
}
