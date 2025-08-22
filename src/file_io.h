#ifndef ALY_COMPILER_FILE_IO_H
#define ALY_COMPILER_FILE_IO_H

#include <stddef.h>
#include <stdio.h>

size_t file_size(FILE* file);
char* file_contents(char* path);

#endif /* ALY_COMPILER_FILE_IO_H */