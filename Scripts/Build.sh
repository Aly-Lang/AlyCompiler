#!/bin/bash

# Navigate to the root directory (one level up from Scripts)
cd ..

# Create a build directory if it doesn't exist
if [ ! -d "build" ]; then
    mkdir build
fi

# Run CMake to configure the project
cmake -S . -B build

# Build the project using the generated Makefiles
cmake --build build

# Optionally, print a message when done
echo "Build complete."
