@echo off
REM Change to the root directory (one level up from scripts/)
cd ..

REM Run CMake configuration
cmake -S . -B bld -G "MinGW Makefiles"
IF ERRORLEVEL 1 (
    echo CMake configuration failed.
    exit /b 1
)

REM Build the project
cmake --build bld
IF ERRORLEVEL 1 (
    echo Build failed.
    exit /b 1
)
