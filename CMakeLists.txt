cmake_minimum_required(VERSION 3.20)

# Use 'ccache' if available to speed up compilation
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# Export compilation database for tooling support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Project definition with Language
project(AlyCompiler C)

# Define the executable target
add_executable(
    alyc
    src/main.c
    src/error.c
    src/file_io.c
    src/parser.c
)

# Include path setup
target_include_directories(
    alyc
    PUBLIC src/
)

# Compiler flags for MSVC and GCC
target_compile_options(alyc PRIVATE
    # Suppress 'undefined function assumed extern returning int' warning (C4013 - MSVC)
    $<$<C_COMPILER_ID:MSVC>:/wd4013>
    # Suppress 'deprecated POSIX function' warning (C4996 - MSVC)
    $<$<C_COMPILER_ID:MSVC>:/wd4996>
    # Suppress 'declaration hides previous local declaration' warning (C4456 - MSVC)
    $<$<C_COMPILER_ID:MSVC>:/wd4456>
    # Suppress equivalent warnings for GCC (ignoring unused variables, deprecated functions)
    $<$<C_COMPILER_ID:GNU>:-Wno-unused-variable -Wno-deprecated-declarations>
)

# Set runtime output directory
set_target_properties(alyc PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
