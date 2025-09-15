# Compile & Build Aly with a file passed to GCC
cd C:/Dev/AlyCompiler && mkdir -p bld && cd bld && cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc .. && mingw32-make && ./bin/alyc.exe -f x86_64-mswin -v ../Examples/Pointers.aly -v


