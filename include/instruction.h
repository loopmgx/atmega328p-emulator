#ifndef OPCODE_H
#define OPCODE_H

#include "./types.h"
#include <stdint.h>

typedef enum {
    PTR_X,
    PTR_X_P, // X+
    PTR_X_M, // X-
    PTR_X_Q, // X+q
    PTR_Y,
    PTR_Y_P,
    PTR_Y_M,
    PTR_Y_Q,
    PTR_Z,
    PTR_Z_P,
    PTR_Z_M,
    PTR_Z_Q
}ptr_type;

typedef struct {
    ptr_type type;
    uint8_t  q;
}ptr_t;

typedef enum {
    INS_ERROR,
    INS_ADC,
    INS_ADD,
    INS_ADIW,
    INS_AND,
    INS_ANDI,
    INS_ASR,
    INS_BCLR,
    INS_BLD,
    INS_BRBC,
    INS_BRBS,
    INS_BREAK,
    INS_BSET,
    INS_BST,
    INS_CALL,
    INS_CBI,
    INS_COM,
    INS_CP,
    INS_CPC,
    INS_CPI,
    INS_CPSE,
    INS_DEC,
    INS_EOR,
    INS_FMUL,
    INS_FMULS,
    INS_FMULSU,
    INS_ICALL,
    INS_IJMP,
    INS_IN,
    INS_INC,
    INS_JMP,
    INS_LD,
    INS_LDI,
    INS_LDS,
    INS_LPM,
    INS_LSR,
    INS_MOV,
    INS_MOVW,
    INS_MUL,
    INS_MULS,
    INS_MULSU,
    INS_NEG,
    INS_NOP,
    INS_OR,
    INS_ORI,
    INS_OUT,
    INS_POP,
    INS_PUSH,
    INS_RCALL,
    INS_RET,
    INS_RETI,
    INS_RJMP,
    INS_ROR,
    INS_SBC,
    INS_SBCI,
    INS_SBI,
    INS_SBIC,
    INS_SBIS,
    INS_SBIW,
    INS_SBRC,
    INS_SBRS,
    INS_SLEEP,
    INS_SPM,
    INS_ST,
    INS_STS,
    INS_SUB,
    INS_SUBI,
    INS_SWAP,
    INS_WDR,
}Opcode;

typedef union {

    // register (Rd/Rr)
    reg_t   R;

    // constant
    uint8_t K;

    // relative/absolute adress
    adrs_t  k;

    // b-th bit (0-7)
    bit_t   b;

    // s-th bit in SREG
    bit_t   s;

    // I/O adress (0-63)
    adrs_t  A;

    // displacement
    uint8_t  q;

    // X/Y/Z
    ptr_t   XYZ;

}Operand;

typedef struct {
    
    // Opcode type
    Opcode type;

    // operand one
    Operand ope1;

    // operand two
    Operand ope2;

}Instruction;

Instruction         decode              (word_t*, word_t* limit);
Opcode              identify            (word_t*);
void                decode_operands     (Instruction*, word_t*);


#endif // OPCODE_H
