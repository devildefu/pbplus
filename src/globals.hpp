#pragma once

#include "global_proxy.hpp"

#define DEFINE_GLOBAL(type, name, address) inline GlobalProxy name{reinterpret_cast<type *>(address)}

DEFINE_GLOBAL(bool, g_fast_scroll, 0x00542A21);
DEFINE_GLOBAL(bool, g_menu_animation, 0x00541110);
DEFINE_GLOBAL(int16_t, g_frame, 0x0052401C);
DEFINE_GLOBAL(bool, g_use_gamedata, 0x00524020);
