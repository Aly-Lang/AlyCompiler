#!/bin/sh

# Go up to the root directory
cd ..

# Run CMake configuration
cmake -S . -B bld -G "MinGW Makefiles"
if [ $? -ne 0 ]; then
    echo "CMake configuration failed."
    exit 1
fi

# Build the project
cmake --build bld
if [ $? -ne 0 ]; then
    echo "Build failed."
    exit 1
fi
