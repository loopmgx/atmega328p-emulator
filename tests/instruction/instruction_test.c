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
    w = 0x2C00; // and r0, r0
    assert(identify(&w) == INS_AND);
    w = 0x2FFF; // and r31, r31
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
    w = 0x9409;
    assert(identify(&w) == INS_BSET);
    w = 0x9479;
    assert(identify(&w) == INS_BSET);

    // BST
    w = 0xFA00;
    assert(identify(&w) == INS_BST);
    w = 0xFBF7;
    assert(identify(&w) == INS_BST);

    print_success(__func__);
}
