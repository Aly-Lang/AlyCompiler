# Aly: A Language for You

![Language](https://img.shields.io/badge/Language-C-blue)
![License](https://img.shields.io/badge/License-MIT-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%20|%20Linux-blue)
![Architecture](https://img.shields.io/badge/Arch-x86--64%20|%20x64-green)

![Aly-Lang LOGO](/Resources/Branding/LOGO.png)

I didn't really have a plan, but I went ahead and started making this compiler from scratch in C anyways. Now we have a functioning compiler for **Aly**, a brand new language.

## Usage

Running the compiler executable with no arguments will display a usage message that contains compiler flags and options as well as command layout.

## Building

### Dependencies

  * [CMake \>= 3.14](https://cmake.org/)
  * Any C Compiler (We like [GCC](https://gcc.gnu.org/))

First, generate a build tree using CMake:

```shell
cmake -B bld
```

Finally, build an executable from the build tree:

```shell
cmake --build bld
```

### To build generated x86\_64 ASM

**GNU Binutils:**

```shell
as code.S -o code.o
ld code.o -o code
```

**GNU Compiler Collection (GCC):**

```shell
gcc code.S -o code.exe
```

**LLVM/Clang:**

```shell
clang code.S -o code.exe --target=x86_64
```

## Language Reference

Aly is **statically typed**. Variables must be declared and type annotated before use.

**Whitespace is ignored** and there are **no required expression delimiters**. That's right: no semi-colons and no forced indent\!

Functions are first-class citizens.

An Aly program comes in the form of a file. The file may contain a series of expressions that will be executed in order, from top to bottom. There is no `main` function or other entry point; control flow starts at the very top of the file and makes its way to the bottom.

Let's take a look at a basic program:
```
fact : integer (n : integer) = integer (n : integer) {
  if n < 2 {
    1
  } else {
    n * fact(n - 1)
  }
}

fact(5)
```

This program will return `120` as a status code. The result of the last expression in the file is the return value. The same holds true for function bodies and if/else bodies.

Variables in a local scope **shadow** variables in a parent scope and may share the same symbolic name.