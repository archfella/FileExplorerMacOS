
## Installation (Windows)

[vcpkg](https://github.com/microsoft/vcpkg) is in use,
see official guide for installation and integration with CMake -
["Tutorial: Install and use packages with CMake"](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started)

In short, to have vcpkg:

```
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
bootstrap-vcpkg.bat
```

Next, vcpkg libraries are expected to be installed globally, for simplicity:

```
:: GLEW
vcpkg install glew
:: GLFW3
vcpkg.exe install glfw3
```

## Build & run

Assuming vcpkg is intalled into %VCPKG_ROOT%, just:

```
cmake -S . -B build ^
    -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake
```

To build (Release configuration):

```
cmake --build build --config Release
```

To run:

```
cd build
Release\FileExplorerMacOS.exe
```
