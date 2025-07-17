# AlyCompiler - A Language For You

![Language](https://img.shields.io/badge/Language-C-blue)
![License](https://img.shields.io/badge/License-MIT-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%20|%20Linux-blue)
![Architecture](https://img.shields.io/badge/Arch-x86--64%20|%20x64-green)

![Aly-Lang LOGO](/Resources/Branding/LOGO.png)

I don't really have a plan, I just want to make a compiler; it sounds fun. There's an example of some code that should be valid and able to be compile in [`example`](examples/example.aly) file.

NOTE: Shell commands shown assume a working directory of this repository.

## Usage

Run the executable from a shell with a path to some source code as the only argument. Currently, we print out the furthest progress we are able to make. Eventually, we will output compiled source code.

## Building

## Dependencies:

- [CMake](https://cmake.org/download/)
- [Any C Compiler](https://gcc.gnu.org/install/download.html)

First generate a build tree using CMake.
```bash
cmake -S . -B bld -G "MinGW Makefiles"
```

Finally, build an executable from the build tree.
```bash
 cmake --build bld
```

However, I have made two scripts in `Scripts` folders to generate the project for GCC, which is what I used but if you find MSVC is more user friendly then you can use this command to generate a solution `CMake -B <folder>` and it will generate the `.sln` file for you.

## Building x86_64 ASM

- On Windows under MinGW:
```bash
as code.S -o code.o
ld code.o -o code.exe && code.exe
```

TODO: On Linux