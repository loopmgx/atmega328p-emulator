#include "../include/loader.h"
#include "../include/error.h"
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int bin_loader(void* dst, const char* path, size_t size)
{
    if (dst == NULL || path == NULL) {
        return warning(-1, __func__, "NULL pointer given!");
    }

    FILE* fp = fopen(path, "rb");
 
    if (fp == NULL) {
        return warning(-2, __func__, "File not found!");
    }

    byte_t* pdst = dst;
    int byte;
    for(size_t i = 0; i < size; i++) {
        byte = fgetc(fp);
        if(byte == EOF) {
            fclose(fp);
            return 0;
        }

        pdst[i] = (byte_t)byte;
    }

    byte = fgetc(fp);
    fclose(fp);

    if (byte != EOF) {
        return warning(-3, __func__, "Files is too large!");
    }

    return 0;
}
