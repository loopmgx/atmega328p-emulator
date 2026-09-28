#include <stddef.h>
#include <stdio.h>

void print_success(const char* func) {
    fprintf(stderr, "%-60s[SUCCESS]\n", func);
}
