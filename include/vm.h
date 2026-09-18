#ifndef VM_H
#define VM_H

#include "./types.h"
#include "./macros.h"
#include "./instruction.h"
#include <stdint.h>

/**
 * Data memory layout:
 *
 * Registers               32 B   (0x0000 - 0x001F)
 * I/O registers           64 B   (0x0020 - 0x005F)
 * Extended I/O registers 160 B   (0x0060 - 0x00FF)
 * SRAM                  2048 B   (0x0100 - 0x08FF)
 */

typedef struct {
    
    // Data memory (SRAM + registers)
    byte_t data_mem[DATA_MEM_SIZE];

    // Program (flash) memory
    word_t prog_mem[PROG_MEM_SIZE];

    // Non-volatile eeprom memory
    byte_t eeprom[EEPROM_SIZE];

    // Program counter
    word_t* PC;

}VM;

void vm_init        (VM*, const char* path);
void vm_run         (VM*);
void vm_step        (VM*);
void vm_execute     (VM*, Instruction);
void vm_advance     (VM*, Instruction);

void*  reg_access   (VM*,  reg_t);
void* sram_access   (VM*, adrs_t);



#endif // VM_H
