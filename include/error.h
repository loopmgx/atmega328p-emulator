#ifndef ERROR_H
#define ERROR_H

#include <stdint.h>

// Error will print warning and exit(ret);
void error (int ret, const char *func, const char *fmt);

// Basic warning
int warning (int ret, const char *func, const char *fmt);

// Out of range warning
int warning_range (int ret, 
                   const char *func,
                   const char *name,
                   uint64_t value,
                   uint64_t max);
                   
#endif // ERROR_H
