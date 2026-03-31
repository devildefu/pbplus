#pragma once

// Attempts to override stdout/stderr using standard I/O functions resulted in crashes or no logs, so custom functions
// are used instead.

#include <format>
#include <windows.h>

#include "config.hpp"

inline HANDLE g_handle_out;

namespace console {
    int init();

    template<typename... Args>
    void print(const std::format_string<Args...> fmt, Args&&... args) {
        if (!g_config.show_console) {
            return;
        }

        const std::string result = std::vformat(fmt.get(), std::make_format_args(args...));
        WriteConsoleA(g_handle_out, result.c_str(), result.length(), nullptr, nullptr);
    }

    template<typename... Args>
    void println(const std::format_string<Args...> fmt, Args&&... args) {
        if (!g_config.show_console) {
            return;
        }

        const std::string result = std::vformat(fmt.get(), std::make_format_args(args...));
        WriteConsoleA(g_handle_out, result.c_str(), result.length(), nullptr, nullptr);
        WriteConsoleA(g_handle_out, "\n", 1, nullptr, nullptr);
    }
}
