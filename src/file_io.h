#ifndef ALY_COMPILER_FILE_IO_H
#define ALY_COMPILER_FILE_IO_H

#include <stdio.h>

long file_size(FILE* file);
char* file_contents(char* path);

#endif // ALY_COMPILER_FILE_IO_H