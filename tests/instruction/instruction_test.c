#include "instruction_test.h"
#include "./../../include/instruction.h"
#include "./../../include/types.h"
#include "./../test_helpers.h"
#include <assert.h>

void identify_test()
{
    word_t w; 

    // ADC
    w = 0x1C00; // adc r0, r0
    assert(identify(&w) == INS_ADC);
    w = 0x1FFF; // adc r31, r31
    assert(identify(&w) == INS_ADC);

    // ADD
    w = 0x0C00; // add r0, r0
    assert(identify(&w) == INS_ADD);
    w = 0x0FFF; // add r31, r31
    assert(identify(&w) == INS_ADD);

    // AND
    w = 0x2000; // and r0, r0
    assert(identify(&w) == INS_AND);
    w = 0x23FF; // and r31, r31
    assert(identify(&w) == INS_AND);

    // ADIW first operand is coded on {24,26,28,30} so 0 -> 24; 1 -> 26 ...
    w = 0x9600; // adiw 0, 0 which actually means: adiw 24, 0
    assert(identify(&w) == INS_ADIW);
    w = 0x96FF; // adiw 4, 63 which actually means adiw 30, 63
    assert(identify(&w) == INS_ADIW);

    // ANDI
    w = 0x7000;
    assert(identify(&w) == INS_ANDI);
    w = 0x7FFF;
    assert(identify(&w) == INS_ANDI);

    // ASR
    w = 0x9405;
    assert(identify(&w) == INS_ASR);
    w = 0x95F5;
    assert(identify(&w) == INS_ASR);

    // BCLR
    w = 0x9488;
    assert(identify(&w) == INS_BCLR);
    w = 0x94F8;
    assert(identify(&w) == INS_BCLR);

    // BLD
    w = 0xF800;
    assert(identify(&w) == INS_BLD);
    w = 0xF9F7;
    assert(identify(&w) == INS_BLD);

    w = 0xF400;
    assert(identify(&w) == INS_BRBC);
    w = 0xF7FF;
    assert(identify(&w) == INS_BRBC);

    w = 0xF000;
    assert(identify(&w) == INS_BRBS);
    w = 0xF3FF;
    assert(identify(&w) == INS_BRBS);

    // BREAK
    w = 0x9598;
    assert(identify(&w) == INS_BREAK);

    w = 0xF001;
    assert(identify(&w) == INS_BREQ);
    w = 0xF3F9;
    assert(identify(&w) == INS_BREQ);

    // BRGE
    w = 0xF404;
    assert(identify(&w) == INS_BRGE);
    w = 0xF7FC;
    assert(identify(&w) == INS_BRGE);

    // BRHC
    w = 0xF405;
    assert(identify(&w) == INS_BRHC);
    w = 0xF7FD;
    assert(identify(&w) == INS_BRHC);

    // BRHS
    w = 0xF005;
    assert(identify(&w) == INS_BRHS);
    w = 0xF3FD;
    assert(identify(&w) == INS_BRHS);

    // BSET
    w = 0x9408;
    assert(identify(&w) == INS_BSET);
    w = 0x9478;
    assert(identify(&w) == INS_BSET);

    // BST
    w = 0xFA00;
    assert(identify(&w) == INS_BST);
    w = 0xFBF7;
    assert(identify(&w) == INS_BST);

    // CALL
    w = 0x940E;
    assert(identify(&w) == INS_CALL);
    w = 0x95FF;
    assert(identify(&w) == INS_CALL);

    w = 0x9800; // A = 0, b = 0
    assert(identify(&w) == INS_CBI);
    w = 0x98FF; // A = 31, b = 7
    assert(identify(&w) == INS_CBI);

    w = 0x9800; // A = 0, b = 0
    assert(identify(&w) == INS_CBI);
    w = 0x98FF; // A = 31, b = 7
    assert(identify(&w) == INS_CBI);

    w = 0x9400;
    assert(identify(&w) == INS_COM);
    w = 0x95F0;
    assert(identify(&w) == INS_COM);

    w = 0x1400;
    assert(identify(&w) == INS_CP);
    w = 0x17FF;
    assert(identify(&w) == INS_CP);

    w = 0x0400;
    assert(identify(&w) == INS_CPC);
    w = 0x07FF;
    assert(identify(&w) == INS_CPC);

    w = 0x3000;
    assert(identify(&w) == INS_CPI);
    w = 0x3FFF;
    assert(identify(&w) == INS_CPI);

    w = 0x3000;
    assert(identify(&w) == INS_CPI);
    w = 0x3FFF;
    assert(identify(&w) == INS_CPI);

    w = 0x1000;
    assert(identify(&w) == INS_CPSE);
    w = 0x13FF;
    assert(identify(&w) == INS_CPSE);

    w = 0x940A;
    assert(identify(&w) == INS_DEC);
    w = 0x95FA;
    assert(identify(&w) == INS_DEC);

    w = 0x940B;
    assert(identify(&w) == INS_DES);
    w = 0x94FB;
    assert(identify(&w) == INS_DES);

    w = 0x2400;
    assert(identify(&w) == INS_EOR);
    w = 0x27FF;
    assert(identify(&w) == INS_EOR);

    w = 0x0308;
    assert(identify(&w) == INS_FMUL);
    w = 0x037F;
    assert(identify(&w) == INS_FMUL);

    w = 0x0380;
    assert(identify(&w) == INS_FMULS);
    w = 0x03F7;
    assert(identify(&w) == INS_FMULS);

    w = 0x0388;
    assert(identify(&w) == INS_FMULSU);
    w = 0x03FF;
    assert(identify(&w) == INS_FMULSU);

    w = 0x9509;
    assert(identify(&w) == INS_ICALL);

    w = 0x9409;
    assert(identify(&w) == INS_IJMP);

    w = 0xB000;
    assert(identify(&w) == INS_IN);
    w = 0xB7FF;
    assert(identify(&w) == INS_IN);

    w = 0x9403;
    assert(identify(&w) == INS_INC);
    w = 0x95F3;
    assert(identify(&w) == INS_INC);

    w = 0x940C;
    assert(identify(&w) == INS_JMP);
    w = 0x95FD;
    assert(identify(&w) == INS_JMP);

    w = 0x9206;
    assert(identify(&w) == INS_LAC);
    w = 0x93F6;
    assert(identify(&w) == INS_LAC);

    w = 0x9205;
    assert(identify(&w) == INS_LAS);
    w = 0x93F5;
    assert(identify(&w) == INS_LAS);

    w = 0x9205;
    assert(identify(&w) == INS_LAS);
    w = 0x93F5;
    assert(identify(&w) == INS_LAS);
    
    w = 0x900C;
    assert(identify(&w) == INS_LD);
    w = 0x91FC;
    assert(identify(&w) == INS_LD);

    w = 0x900D;
    assert(identify(&w) == INS_LD);
    w = 0x91FD;
    assert(identify(&w) == INS_LD);

    w = 0x900E;
    assert(identify(&w) == INS_LD);
    w = 0x91FE;
    assert(identify(&w) == INS_LD);

    w = 0x8008;
    assert(identify(&w) == INS_LD);
    w = 0x81F8;
    assert(identify(&w) == INS_LD);

    w = 0x9009;
    assert(identify(&w) == INS_LD);
    w = 0x91F9;
    assert(identify(&w) == INS_LD);

    w = 0x900A;
    assert(identify(&w) == INS_LD);
    w = 0x91FA;
    assert(identify(&w) == INS_LD);

    w = 0x8008;
    assert(identify(&w) == INS_LD);
    w = 0xADFF;
    assert(identify(&w) == INS_LD);

    w = 0x8000;
    assert(identify(&w) == INS_LD);
    w = 0x81F0; 
    assert(identify(&w) == INS_LD);

    w = 0x9001;
    assert(identify(&w) == INS_LD);
    w = 0x91F1; 
    assert(identify(&w) == INS_LD);

    w = 0x9002;
    assert(identify(&w) == INS_LD);
    w = 0x91F2;
    assert(identify(&w) == INS_LD);

    w = 0x8000;
    assert(identify(&w) == INS_LD);
    w = 0xADF7;
    assert(identify(&w) == INS_LD);

    w = 0xE000;
    assert(identify(&w) == INS_LDI);
    w = 0xEFFF;
    assert(identify(&w) == INS_LDI);

    w = 0x9000;
    assert(identify(&w) == INS_LDS);
    w = 0x91F0;
    assert(identify(&w) == INS_LDS);
    
    w = 0xA000;
    assert(identify(&w) == INS_LDS);
    w = 0xA7FF;
    assert(identify(&w) == INS_LDS);

    w = 0x95C8;
    assert(identify(&w) == INS_LPM);
    
    w = 0x9004;
    assert(identify(&w) == INS_LPM);
    w = 0x91F4;
    assert(identify(&w) == INS_LPM);

    w = 0x9004;
    assert(identify(&w) == INS_LPM);
    w = 0x91F5;
    assert(identify(&w) == INS_LPM);

    w = 0x2C00;
    assert(identify(&w) == INS_MOV);
    w = 0x2FFF;
    assert(identify(&w) == INS_MOV);

    w = 0x0100;
    assert(identify(&w) == INS_MOVW);
    w = 0x01FF;
    assert(identify(&w) == INS_MOVW);

    w = 0x9C00;
    assert(identify(&w) == INS_MUL);
    w = 0x9FFF;
    assert(identify(&w) == INS_MUL);

    w = 0x0200;
    assert(identify(&w) == INS_MULS);
    w = 0x02FF;
    assert(identify(&w) == INS_MULS);

    w = 0x0300;
    assert(identify(&w) == INS_MULSU);
    w = 0x0377;
    assert(identify(&w) == INS_MULSU);

    w = 0x9401;
    assert(identify(&w) == INS_NEG);
    w = 0x95F1;
    assert(identify(&w) == INS_NEG);

    w = 0x0000;
    assert(identify(&w) == INS_NOP);

    w = 0x2800;
    assert(identify(&w) == INS_OR);
    w = 0x2BFF;
    assert(identify(&w) == INS_OR);

    w = 0x6000;
    assert(identify(&w) == INS_ORI);
    w = 0x6FFF;
    assert(identify(&w) == INS_ORI);

    w = 0xB800;
    assert(identify(&w) == INS_OUT);
    w = 0xBFFF;
    assert(identify(&w) == INS_OUT);

    w = 0x900F;
    assert(identify(&w) == INS_POP);
    w = 0x91FF;
    assert(identify(&w) == INS_POP);

    w = 0x920F;
    assert(identify(&w) == INS_PUSH);
    w = 0x93FF;
    assert(identify(&w) == INS_PUSH);

    w = 0x6000;
    assert(identify(&w) == INS_ORI);
    w = 0x6FFF;
    assert(identify(&w) == INS_ORI);

    w = 0x9508;
    assert(identify(&w) == INS_RET);

    w = 0x9518;
    assert(identify(&w) == INS_RETI);

    w = 0xC000;
    assert(identify(&w) == INS_RJMP);
    w = 0xCFFF;
    assert(identify(&w) == INS_RJMP);

    w = 0x9407;
    assert(identify(&w) == INS_ROR);
    w = 0x95F7;
    assert(identify(&w) == INS_ROR);

    w = 0x0800;
    assert(identify(&w) == INS_SBC);
    w = 0x0BFF;
    assert(identify(&w) == INS_SBC);

    w = 0x4000;
    assert(identify(&w) == INS_SBCI);
    w = 0x4FFF;
    assert(identify(&w) == INS_SBCI);

    w = 0x9A00;
    assert(identify(&w) == INS_SBI);
    w = 0x9AFF;
    assert(identify(&w) == INS_SBI);

    w = 0x9900;
    assert(identify(&w) == INS_SBIC);
    w = 0x99FF;
    assert(identify(&w) == INS_SBIC);

    w = 0x9B00;
    assert(identify(&w) == INS_SBIS);
    w = 0x9BFF;
    assert(identify(&w) == INS_SBIS);

    w = 0x9700;
    assert(identify(&w) == INS_SBIW);
    w = 0x97FF;
    assert(identify(&w) == INS_SBIW);

    w = 0xFC00;
    assert(identify(&w) == INS_SBRC);
    w = 0xFDF7;
    assert(identify(&w) == INS_SBRC);

    w = 0xFE00;
    assert(identify(&w) == INS_SBRS);
    w = 0xFEF7;
    assert(identify(&w) == INS_SBRS);

    w = 0x9588;
    assert(identify(&w) == INS_SLEEP);

    w = 0x95E8;
    assert(identify(&w) == INS_SPM);

    w = 0xFC00;   // SBRC r0, 0
    assert(identify(&w) == INS_SBRC);

    w = 0xFDF7;   // SBRC r31, 7
    assert(identify(&w) == INS_SBRC);

    w = 0x920C;
    assert(identify(&w) == INS_ST);
    w = 0x93FC;
    assert(identify(&w) == INS_ST);

    w = 0x920D;
    assert(identify(&w) == INS_ST);
    w = 0x93FD;
    assert(identify(&w) == INS_ST);

    w = 0x920E;
    assert(identify(&w) == INS_ST);
    w = 0x93FE;
    assert(identify(&w) == INS_ST);

    w = 0x8208;
    assert(identify(&w) == INS_ST);
    w = 0x83F8;
    assert(identify(&w) == INS_ST);

    w = 0x9209;
    assert(identify(&w) == INS_ST);
    w = 0x93F9;
    assert(identify(&w) == INS_ST);

    w = 0x920A;
    assert(identify(&w) == INS_ST);
    w = 0x93FA;
    assert(identify(&w) == INS_ST);

    w = 0x8208;
    assert(identify(&w) == INS_ST);
    w = 0x83F8;
    assert(identify(&w) == INS_ST);

    w = 0x8200;
    assert(identify(&w) == INS_ST);
    w = 0x83F0;
    assert(identify(&w) == INS_ST);

    w = 0x9201;
    assert(identify(&w) == INS_ST);
    w = 0x93F1;
    assert(identify(&w) == INS_ST);

    w = 0x9202;
    assert(identify(&w) == INS_ST);
    w = 0x93F2;
    assert(identify(&w) == INS_ST);

    w = 0x9202;
    assert(identify(&w) == INS_ST);
    w = 0x93F2;
    assert(identify(&w) == INS_ST);

    w = 0x8200;
    assert(identify(&w) == INS_ST);
    w = 0xAFF7;
    assert(identify(&w) == INS_ST);

    w = 0x9200;
    assert(identify(&w) == INS_STS);
    w = 0x93F0;
    assert(identify(&w) == INS_STS);

    w = 0x1800;
    assert(identify(&w) == INS_SUB);
    w = 0x1BFF;
    assert(identify(&w) == INS_SUB);

    w = 0x5000;
    assert(identify(&w) == INS_SUBI);
    w = 0x5FFF;
    assert(identify(&w) == INS_SUBI);

    w = 0x9402;
    assert(identify(&w) == INS_SWAP);
    w = 0x95F2;
    assert(identify(&w) == INS_SWAP);

    w = 0x95A8;
    assert(identify(&w) == INS_WDR);

    print_success(__func__);
}
