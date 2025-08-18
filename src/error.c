#include <error.h>

#include <assert.h>
#include <stddef.h>
#include <stdio.h>

Error ok = { ERROR_NONE, NULL };

void print_error(Error err) {
    if (err.type == ERROR_NONE) { return; }
    printf("ERROR: ");
    assert(ERROR_MAX == 6);
    switch (err.type) {
    default:
        printf("Unknown error type...");
        break;
    case ERROR_TODO:
        printf("TODO (not implemented)");
        break;
    case ERROR_SYNTAX:
        printf("Invalid syntax");
        break;
    case ERROR_TYPE:
        printf("Mismatched types");
        break;
    case ERROR_ARGUMENTS:
        printf("Invalid arguments");
        break;
    case ERROR_GENERIC:
        break;
    case ERROR_NONE:
        break;
    }
    putchar('\n');
    if (err.msg) {
        printf("     : %s\n", err.msg);
    }
}