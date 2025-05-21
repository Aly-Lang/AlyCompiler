@echo off
REM Navigate to the root directory (one level up from Scripts)
cd ..

REM Create a build directory if it doesn't exist
if not exist build (
    mkdir build
)

REM Run CMake to configure the project
cmake -S . -B build

REM Build the project using the generated Makefiles
cmake --build build

REM Pause to view any output (optional)
pause
