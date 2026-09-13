#include "./../include/error.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

void error(int ret, const char* func, const char* fmt)
{
    fprintf(stderr, "%s: ", func);
    fprintf(stderr, "%s\n", fmt);
    exit(ret);
}

int warning(int ret, const char *func, const char *fmt)
{
    
#if defined(WARNING_MODE)
    fprintf(stderr, "%s: ", func);
    fprintf(stderr, "%s\n", fmt);
#endif

    return ret;
}

int warning_range(int ret,
                  const char *func,
                  const char *name,
                  uint64_t value,
                  uint64_t max)
{
#if defined(WARNING_MODE)
    fprintf(stderr,
            "%s: %s=%" PRIu64 " exceeds maximum %" PRIu64 "\n",
            func, name, value, max);
#endif
    return ret;
}
