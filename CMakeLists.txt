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

# Source files
set(SOURCE_FILES
    src/main.c
    src/error.c
    src/file_io.c
    src/parser.c
    src/environment.c
    src/codegen.c
    src/typechecker.c
)

# Define executable
add_executable(alyc ${SOURCE_FILES})

# Include directories
target_include_directories(alyc PUBLIC src)

# Compiler flags - warnings off
target_compile_options(alyc PRIVATE
    # MSVC
    $<$<C_COMPILER_ID:MSVC>:/utf-8 /w>

    # GCC / MinGW
    $<$<C_COMPILER_ID:GNU>:-w>

    # Clang
    $<$<C_COMPILER_ID:Clang>:-w>
)

# Ensure C standard is set based on compiler
if (CMAKE_C_COMPILER_ID MATCHES "MSVC")
    target_compile_features(alyc PRIVATE c_std_11)
elseif (CMAKE_C_COMPILER_ID MATCHES "GNU" OR CMAKE_C_COMPILER_ID MATCHES "Clang")
    target_compile_features(alyc PRIVATE c_std_99)
endif()

# Output directories
set_target_properties(alyc PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

# Prevent MinGW GCC from pulling in old MSVC libs like oldnames
if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_C_STANDARD_LIBRARIES "")
endif()

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Set build type to Release or Debug" FORCE)
endif()
