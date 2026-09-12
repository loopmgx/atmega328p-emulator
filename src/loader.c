#include "../include/loader.h"
#include "../include/error.h"
#include <limits.h>
#include <stddef.h>
#include <stdio.h>

int bin_loader(void* dst, const char* path, size_t size)
{
    if (dst == NULL || path == NULL) {
        return warning("NULL pointer given!", __func__, -1);
    }

    FILE* fp = fopen(path, "rb");
 
    if (fp == NULL) {
        return warning("File not found!", __func__, -2);
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
        return warning("Files is too large!", __func__, -3);
    }

    return 0;
}
