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
    src/codegen.c
    src/error.c
    src/environment.c
    src/file_io.c
    src/main.c
    src/parser.c
    src/typechecker.c
    src/codegen/intermediate_representation.c
    src/codegen/register_allocation.c
    src/codegen/x86_64/arch_x86_64.c
)

# Define executable
add_executable(alyc ${SOURCE_FILES})

# Include directories
target_include_directories(alyc PUBLIC src)

# Compiler flags - warnings on
target_compile_options(alyc PRIVATE
    # MSVC: enable all warnings
    # $<$<C_COMPILER_ID:MSVC>:/W4 /permissive->

    # GCC / MinGW: enable common warnings and treat warnings as errors optionally
    # $<$<C_COMPILER_ID:GNU>:-Wall -Wextra -Wpedantic>

    # Clang: similar to GCC
    # $<$<C_COMPILER_ID:Clang>:-Wall -Wextra -Wpedantic>
)

target_compile_definitions(
    alyc
    PRIVATE
    _FORTIFY_SOURCE=3
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
