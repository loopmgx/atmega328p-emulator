#include "./../include/error.h"
#include <stdio.h>
#include <stdlib.h>

void error(const char* fmt, const char* func, int ret)
{
    fprintf(stderr, "%s: ", func);
    fprintf(stderr, "%s\n", fmt);
    exit(ret);
}

int warning(const char *fmt, const char *funct, int ret)
{
    
#if defined(WARNING_MODE)
    fprintf(stderr, "%s: ", funct);
    fprintf(stderr, "%s\n", fmt);
#endif

    return ret;
}
