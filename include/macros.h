#ifndef MACROS_H
#define MACROS_H

#include <limits.h>

#if CHAR_BIT != 8
    #error "Unsupported architecture: CHAR_BIT must be 8"
#endif

// size (in bytes) of data memory (SRAM + registers)
#define DATA_MEM_SIZE (0x0900u)

#define SRAM_SIZE     (0x0800u)

#define SRAM_OFFSET   (0x0100u)

// number (in words) of Program (flash) memory
#define PROG_MEM_SIZE (0x4000u)

// size (in bytes) of non-volatile eeprom memory
#define EEPROM_SIZE   (1024u)

// number of bits in single byte
#define EIGHT_BITS    (8u)

#define SREG_ADRS     (0x05F)

// aboslute adresses of double regs pointers in data memory (low bytes)
#define X_PTR_ADRS    (0x001A)
#define Y_PTR_ADRS    (0x001C)
#define Z_PTR_ADRS    (0x001E)

#endif //MACROS_H
