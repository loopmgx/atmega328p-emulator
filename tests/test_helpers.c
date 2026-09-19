#include <stddef.h>
#include <stdio.h>
#include <string.h>

void print_success(const char* func) {
    size_t size = 40 - strlen(func);

    fprintf(stderr, "%-20s[SUCCESS]\n", func);
}
