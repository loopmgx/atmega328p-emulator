#include "./../include/macros.h"
#include "./../include/flags.h"
#include "./../include/types.h"
#include "./../include/vm.h"
#include <stdbool.h>

void set_flag (VM* vm, Flag fl, bool b)
{
    reg_t* SREG = sreg_access(vm);
    
    if((b)) {
        *SREG |=  (reg_t)fl;
    } else {
        *SREG &= ~(reg_t)fl;
    }
}

bool get_flag (VM* vm, Flag fl)
{
    reg_t* SREG = sreg_access(vm);
    return (*SREG & fl) != 0;
}

reg_t* sreg_access (VM* vm) 
{
    return &vm->data_mem[SREG_ADRS];
}

void set_s_flag(VM* vm)
{
    bool N = get_flag(vm, FLAG_N);
    bool V = get_flag(vm, FLAG_V);

    set_flag(vm, FLAG_S, N != V);
}
