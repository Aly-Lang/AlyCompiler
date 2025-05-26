#!/bin/bash

# Navigate to the root directory (one level up from Scripts)
cd ..

# Create a build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir bld
fi

# Run CMake to configure the project for Visual Studio 2022
cmake -S . -B bld -G "Visual Studio 17 2022"

# Build the project in Debug mode
cmake --build bld --config Debug

# Optionally, print a message when done
echo "Build complete."