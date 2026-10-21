#include "./../include/vm.h"
#include "./../include/error.h"
#include "./../include/loader.h"
#include "./../include/instruction.h"
#include <limits.h>
#include <stdbool.h>
#include <stdlib.h>

void vm_init(VM* vm, const char* path)
{
    if(vm == NULL) {
        error(EXIT_FAILURE, __func__, "NULL poointer given!");
    }

    if(path == NULL) {
        warning(0, __func__, "No program file given!");
        return;
    }

    // loading bin program data
    bin_loader(vm->prog_mem, path, PROG_MEM_SIZE);

    // set program counter to start of program memory
    vm->PC = vm->prog_mem;
}

void vm_run(VM* vm) 
{
    while(true) {
        vm_step(vm);
    }
}

void vm_step(VM* vm) 
{
    Instruction i = decode(vm->PC, vm->prog_mem + PROG_MEM_SIZE);
    vm_execute(vm, i);
}

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

adrs_t get_x (VM* vm) 
{
    adrs_t adrs;
    adrs = vm->data_mem[X_PTR_ADRS];
    adrs |= vm->data_mem[X_PTR_ADRS + 1] << (sizeof(byte_t) * CHAR_BIT);
    return adrs;
}

adrs_t get_y (VM* vm)
{
    adrs_t adrs;
    adrs = vm->data_mem[Y_PTR_ADRS];
    adrs |= vm->data_mem[Y_PTR_ADRS + 1] << (sizeof(byte_t) * CHAR_BIT);
    return adrs;
}

adrs_t get_z (VM* vm) 
{
    adrs_t adrs;
    adrs = vm->data_mem[Z_PTR_ADRS];
    adrs |= vm->data_mem[Z_PTR_ADRS + 1] << (sizeof(byte_t) * CHAR_BIT);
    return adrs;
}

void set_x (VM* vm, adrs_t val) 
{
    byte_t low;
    byte_t high;

    low = val;
    high = val >> sizeof(byte_t) * CHAR_BIT;
    
    vm->data_mem[X_PTR_ADRS] = low;
    vm->data_mem[X_PTR_ADRS + 1] = high;
}

void set_y (VM* vm, adrs_t val) 
{
    byte_t low;
    byte_t high;

    low = val;
    high = val >> sizeof(byte_t) * CHAR_BIT;
    
    vm->data_mem[Y_PTR_ADRS] = low;
    vm->data_mem[Y_PTR_ADRS + 1] = high;
}

void set_z (VM* vm, adrs_t val)
{
    byte_t low;
    byte_t high;

    low = val;
    high = val >> sizeof(byte_t) * CHAR_BIT;
    
    vm->data_mem[Z_PTR_ADRS] = low;
    vm->data_mem[Z_PTR_ADRS + 1] = high;
}
