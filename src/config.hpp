#pragma once

struct Config {
    bool no_scroll = false;
    bool no_menu_animation = false;
    bool no_intro = false;
    bool no_gamedata = false;

    // Developer settings.
    bool show_console = false;

    int load(const char *path);
};

inline Config g_config;
