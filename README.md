# pbplus

A small modification for "Bob's Adventure" that adds several enhancements:

- Option to disable scroll animation
- Option to disable menu animation
- Option to disable the intro cutscene
- Option to disable gamedata
- Fix for an unintended display brightness changes

**Compatibility:** Supports version 1.0.3 (Windows only).

## Installation

1. Download `libpbloader.dll` from [the latest release](https://example.com).
2. Download the patched executable from [here](https://example.com).
3. Place both files in the game's installation directory.

## Configuration

Create a configuration file named `pbplus.ini` in the game's directory.

- View all available options: [Sample configuration file](https://example.com)
- Or, copy the sample file to your directory and modify it as needed.

## Building

Prerequisites:
- MinGW-w64 (for i686)
- SDL2
- CMake
- Ninja (Optional; if not used, remove `-G Ninja` from commands)

### Windows

#### Debug build

```shell
$ cmake . -B build -G Ninja
$ cmake --build build
```

#### Release build

```shell
$ cmake . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```

### Linux

#### Debug build

```shell
$ cmake . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=i686-w64-mingw32-gcc.cmake
$ cmake --build build
```

#### Release build

```shell
$ cmake . -B build -G Ninja -DCMAKE_TOOLCHAIN_FILE=i686-w64-mingw32-gcc.cmake -DCMAKE_BUILD_TYPE=Release
$ cmake --build build
```
