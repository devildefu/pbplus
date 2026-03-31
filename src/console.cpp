#include "console.hpp"

#include <windows.h>

namespace console {
    int init() {
        if (!g_config.show_console) {
            return 0;
        }

        if (AllocConsole() == 0) {
            return -1;
        }

        g_handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
        if (g_handle_out == INVALID_HANDLE_VALUE) {
            return -1;
        }

        return 0;
    }
}
