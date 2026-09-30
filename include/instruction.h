#ifndef OPCODE_H
#define OPCODE_H

#include "./types.h"
#include <stdint.h>

typedef enum {
    PTR_X,
    PTR_X_P,
    PTR_X_M,
    PTR_Y,
    PTR_Y_P,
    PTR_Y_M,
    PTR_Z,
    PTR_Z_P,
    PTR_Z_M
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
    INS_BRCC,
    INS_BRCS,
    INS_BREAK,
    INS_BREQ,
    INS_BRGE,
    INS_BRHC,
    INS_BRHS,
    INS_BRID,
    INS_BRIE,
    INS_BRLO,
    INS_BRLT,
    INS_BRMI,
    INS_BRNE,
    INS_BRPL,
    INS_BRSH,
    INS_BRTC,
    INS_BRTS,
    INS_BRVC,
    INS_BRVS,
    INS_BSET,
    INS_BST,
    INS_CALL,
    INS_CBI,
    INS_CBR,
    INS_CLC,
    INS_CLH,
    INS_CLI,
    INS_CLN,
    INS_CLR,
    INS_CLS,
    INS_CLT,
    INS_CLV,
    INS_CLZ,
    INS_COM,
    INS_CP,
    INS_CPC,
    INS_CPI,
    INS_CPSE,
    INS_DEC,
    INS_DES,
    INS_EOR,
    INS_FMUL,
    INS_FMULS,
    INS_FMULSU,
    INS_ICALL,
    INS_IJMP,
    INS_IN,
    INS_INC,
    INS_JMP,
    INS_LAC,
    INS_LAS,
    INS_LD,
    INS_LDI,
    INS_LDS,
    INS_LPM,
    INS_LSL,
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
    INS_ROL,
    INS_ROR,
    INS_SBC,
    INS_SBCI,
    INS_SBI,
    INS_SBIC,
    INS_SBIS,
    INS_SBIW,
    INS_SBR,
    INS_SBRC,
    INS_SBRS,
    INS_SEC,
    INS_SEH,
    INS_SEI,
    INS_SEN,
    INS_SER,
    INS_SES,
    INS_SET,
    INS_SEV,
    INS_SEZ,
    INS_SLEEP,
    INS_SPM,
    INS_ST,
    INS_STS,
    INS_STD,
    INS_SUB,
    INS_SUBI,
    INS_SWAP,
    INS_TST,
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
    ptr_t   XZY;

}Operand;

typedef struct {
    
    // Opcode type
    Opcode type;

    // operand one
    Operand ope1;

    // operand two
    Operand ope2;

}Instruction;

Instruction decode (word_t*, word_t* limit);
void decode_operands (Instruction*);
Opcode identify (word_t*);


#endif // OPCODE_H
