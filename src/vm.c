#include "./../include/vm.h"
#include "./../include/error.h"    

void* reg_access (VM* vm, reg_t reg) {

    if(reg >= 32) {
        warning_range(-1, __func__, "register", reg, 31);
    }

    return &vm->data_mem[reg];
}

void* sram_access (VM* vm, adrs_t adrs) {
    adrs += SRAM_OFFSET;

    if(adrs >= DATA_MEM_SIZE) {
        warning_range(-1, __func__, "sram", adrs, DATA_MEM_SIZE);
    }

    return &vm->data_mem[adrs];
}
