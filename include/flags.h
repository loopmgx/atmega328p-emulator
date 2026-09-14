#ifndef FLAGS_H
#define FLAGS_H

#include "./macros.h"
#include "./types.h"
#include "./vm.h"
#include <stdbool.h>

typedef enum {
    FLAG_C = (1 << 0),
    FLAG_Z = (1 << 1),
    FLAG_N = (1 << 2),
    FLAG_V = (1 << 3),
    FLAG_S = (1 << 4),
    FLAG_H = (1 << 5),
    FLAG_T = (1 << 6),
    FLAG_I = (1 << 7)
} Flag;

reg_t* sreg_access (VM*);

void set_flag      (VM*, Flag, bool);
bool get_flag      (VM*, Flag);
void set_s_flag    (VM*);


#endif // FLAGS_H
