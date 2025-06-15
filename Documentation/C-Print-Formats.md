# C `printf` Format Specifiers

| Specifier | Meaning                          | Notes / Example |
|:----------|:----------------------------------|:----------------|
| `%d`, `%i` | Signed decimal integer            | Example: `printf("%d", -42);` |
| `%u`      | Unsigned decimal integer           | Example: `printf("%u", 42);` |
| `%f`      | Decimal floating-point (fixed)     | Example: `printf("%f", 3.1415);` |
| `%F`      | Same as `%f`, but uppercase         | Example: `printf("%F", 3.1415);` |
| `%e`      | Scientific notation (lowercase)     | Example: `printf("%e", 3.1415);` |
| `%E`      | Scientific notation (uppercase)     | Example: `printf("%E", 3.1415);` |
| `%g`      | Shorter of `%e` or `%f`             | Example: `printf("%g", 3.1415);` |
| `%G`      | Shorter of `%E` or `%F`             | Example: `printf("%G", 3.1415);` |
| `%c`      | Single character                   | Example: `printf("%c", 'A');` |
| `%s`      | String of characters                | Example: `printf("%s", "Hello");` |
| `%p`      | Pointer address                    | Example: `printf("%p", (void *)ptr);` |
| `%%`      | Literal `%` sign                   | Example: `printf("%%");` |

---

## Length Modifiers

Length modifiers adjust the size/type of the data.

| Modifier | Meaning                           | Used With |
|:---------|:----------------------------------|:----------|
| `hh`     | Signed/unsigned `char`             | `%hhd`, `%hhu` |
| `h`      | Signed/unsigned `short`            | `%hd`, `%hu` |
| `l`      | Signed/unsigned `long`             | `%ld`, `%lu`, `%lf` |
| `ll`     | Signed/unsigned `long long`        | `%lld`, `%llu` |
| `j`      | `intmax_t` / `uintmax_t` types      | `%jd`, `%ju` |
| `z`      | `size_t` / `ssize_t`                | `%zd`, `%zu` |
| `t`      | `ptrdiff_t`                        | `%td`, `%tu` |
| `L`      | `long double`                      | `%Lf` |

---

## Common Specifier Combos

| Combo      | Meaning                                  |
|:-----------|:-----------------------------------------|
| `%ld`      | Signed long integer                     |
| `%lu`      | Unsigned long integer                   |
| `%lld`     | Signed long long integer                |
| `%llu`     | Unsigned long long integer              |
| `%zd`      | Signed `size_t` (aka `ssize_t`)          |
| `%zu`      | Unsigned `size_t`                       |
| `%jd`      | Signed `intmax_t` (very large integer)   |
| `%ju`      | Unsigned `uintmax_t`                    |
| `%Lf`      | `long double` floating point            |

---

## Quick Example

```c
#include <stdio.h>

int main() {
    int i = -42;
    unsigned int u = 42;
    float f = 3.1415;
    long long ll = 12345678901234LL;

    printf("%d %u %f %lld\n", i, u, f, ll);
    return 0;
}