#include <windows.h>

#include "config.hpp"
#include "console.hpp"
#include "globals.hpp"
#include "hooks.hpp"

HANDLE g_thread;

DWORD WINAPI pbp_main(LPVOID) {
    if (g_config.load("pbplus.ini") < 0) {
        MessageBoxA(nullptr, "Failed to load config.ini", "Error", MB_OK);
        return 1;
    }

    if (console::init() < 0) {
        MessageBoxA(nullptr, "Failed to initialize console", "Error", MB_OK);
        return 1;
    }

    console::println("Console test, please ignore");

    g_use_gamedata = !g_config.no_gamedata;

    if (hooks::init() < 0) {
        MessageBoxA(nullptr, "Could not initialize hooks.", "Error", MB_OK);
        return 1;
    }
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason, LPVOID reserved) {
    switch (reason) {
        case DLL_PROCESS_ATTACH:
            g_thread = CreateThread(nullptr, 0, &pbp_main, nullptr, 0, nullptr);
            break;
        default:
            break;
    }
    return TRUE;
}

// Required by the patched executable.
extern "C" void dog() {}
