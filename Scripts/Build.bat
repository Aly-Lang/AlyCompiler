@echo off
cd ..

REM Explicitly force GCC toolchain
cmake -S . -B bld -G "MinGW Makefiles" ^
  -DCMAKE_C_COMPILER=gcc ^
  -DCMAKE_CXX_COMPILER=g++ ^
  -DCMAKE_SYSTEM_NAME=Windows ^
  -DCMAKE_BUILD_TYPE=Debug

IF ERRORLEVEL 1 (
    echo CMake configuration failed.
    exit /b 1
)

cmake --build bld
IF ERRORLEVEL 1 (
    echo Build failed.
    exit /b 1
)
