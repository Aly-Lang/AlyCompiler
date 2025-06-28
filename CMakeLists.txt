cmake_minimum_required(VERSION 3.20)

# Project definition
project(AlyCompiler C)

# Use 'ccache' if available
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Define executable
add_executable(alyc
    src/main.c
    src/error.c
    src/file_io.c
    src/parser.c
    src/environment.c
    src/codegen.c
    src/typechecker.c
)

# Include directories
target_include_directories(alyc PUBLIC src)

# Compiler flags
target_compile_options(alyc PRIVATE
    # MSVC flags
    $<$<C_COMPILER_ID:MSVC>:/wd4013 /wd4996 /wd4456>

    # MinGW/GCC flags
    $<$<C_COMPILER_ID:GNU>:
        -Wall
        -Wextra
        -pedantic
        -Wno-unused-variable
        -Wno-deprecated-declarations
    >

    # Clang flags
    $<$<C_COMPILER_ID:Clang>:
        -Wall
        -Wextra
        -Wno-unused-variable
        -Wno-deprecated-declarations
    >
)

# Optional: Ensure C standard is set based on compiler
if (CMAKE_C_COMPILER_ID MATCHES "MSVC")
    target_compile_features(alyc PRIVATE c_std_11)  # Use C11 for MSVC
elseif (CMAKE_C_COMPILER_ID MATCHES "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_features(alyc PRIVATE c_std_99)  # Use C99 for MinGW/GCC/Clang
endif()

# Output directory
set_target_properties(alyc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Optional: Set default build type if not defined (e.g., Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Set build type to Release or Debug" FORCE)
endif()
