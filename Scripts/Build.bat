@echo off
REM Navigate to the root directory (one level up from Scripts)
cd ..

REM Create a build directory if it doesn't exist
if not exist build (
    mkdir build
)

REM Run CMake to configure the project for Visual Studio 2022
cmake -S . -B build -G "Visual Studio 17 2022"

REM Build the project in Debug mode
cmake --build build --config Debug

REM Pause to view any output (optional)
pause