cmake_minimum_required(VERSION 4.0)
project(pbplus VERSION 0.0 LANGUAGES C CXX)

if(NOT CMAKE_SYSTEM_NAME MATCHES Windows)
    message(FATAL_ERROR "The target system must be Windows")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_library(pbplus SHARED
        src/detours/hde32/hde32.cpp
        src/inih/ini.c
        src/inih/cpp/INIReader.cpp

        src/main.cpp
        src/globals.hpp
        src/global_proxy.hpp
        src/hooks.hpp
        src/hooks.cpp
        src/console.hpp
        src/console.cpp
        src/game.hpp
        src/util.hpp
        src/config.hpp
        src/config.cpp
)
target_compile_features(pbplus PRIVATE cxx_std_20)
set_target_properties(pbplus PROPERTIES CXX_EXTENSIONS OFF OUTPUT_NAME "pbloader")
target_include_directories(pbplus PRIVATE src)

find_package(SDL2 REQUIRED)
target_link_libraries(pbplus PRIVATE SDL2::SDL2)
