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
)

# Include directories
target_include_directories(alyc PUBLIC src)

# Compiler flags
target_compile_options(alyc PRIVATE
    $<$<C_COMPILER_ID:MSVC>:/wd4013 /wd4996 /wd4456>
    $<$<C_COMPILER_ID:GNU>:-Wno-unused-variable -Wno-deprecated-declarations>
    $<$<C_COMPILER_ID:Clang>:-Wno-unused-variable -Wno-deprecated-declarations>
)

# Output directory
set_target_properties(alyc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
