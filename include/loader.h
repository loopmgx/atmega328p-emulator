#ifndef LOADER_H
#define LOADER_H

#include "./vm.h"
#include <stddef.h>
#include <stdio.h>

int bin_loader(void* dst, const char* path, size_t size);

#endif // LOADER_H
