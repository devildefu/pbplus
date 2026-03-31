#include "hooks.hpp"

#include <SDL.h>
#include <memory>
#include <windows.h>

#include "config.hpp"
#include "console.hpp"
#include "detours/detours.h"
#include "game.hpp"
#include "globals.hpp"
#include "util.hpp"

using namespace MologieDetours;

constexpr auto SDL_LIB = "SDL2.dll";

static int was_renderer_created = false;

typedef SDL_Renderer *(*tCreateRenderer)(SDL_Window *, int ,Uint32);
std::unique_ptr<Detour<tCreateRenderer>> create_renderer = nullptr;

typedef int (*tSetWindowBrightness)(SDL_Window *, float);
std::unique_ptr<Detour<tSetWindowBrightness>> set_window_brightness = nullptr;

typedef int (*tAppIntro)();
std::unique_ptr<Detour<tAppIntro>> app_intro = nullptr;

namespace hooks {
    SDL_Renderer *SDL_CreateRenderer(SDL_Window *window, int index, Uint32 flags) {
        SDL_Renderer *renderer = create_renderer->GetOriginalFunction()(window, index, flags);

        // Avoid repeating this if the window is recreated when game settings change.
        if (!was_renderer_created) {
            if (g_config.no_scroll) {
                g_fast_scroll = g_config.no_scroll;
            }
            if (g_config.no_menu_animation) {
                g_menu_animation = g_config.no_menu_animation;
            }

            was_renderer_created = true;
        }

        return renderer;
    }

    // SDL_SetWindowBrightness changes DISPLAY brightness, not window.
    int SDL_SetWindowBrightness(SDL_Window *, float brightness) {
        return 0;
    }

    int AppIntro() {
        if (g_config.no_intro) {
            g_frame = to_underlying(Frame::Game);
            return 0;
        }

        return app_intro->GetOriginalFunction()();
    }

    int init() {
        try {
            create_renderer = std::make_unique<Detour<tCreateRenderer>>(SDL_LIB, "SDL_CreateRenderer", SDL_CreateRenderer);
            set_window_brightness = std::make_unique<Detour<tSetWindowBrightness>>(SDL_LIB, "SDL_SetWindowBrightness", SDL_SetWindowBrightness);
            app_intro = std::make_unique<Detour<tAppIntro>>(reinterpret_cast<tAppIntro>(0x0043C730), AppIntro);
        } catch (DetourException &e) {
            MessageBoxA(nullptr, e.what(), "Error", MB_OK);
            return -1;
        }

        return 0;
    }
}
