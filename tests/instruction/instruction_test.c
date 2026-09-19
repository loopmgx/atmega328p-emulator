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

    print_success(__func__);
}
