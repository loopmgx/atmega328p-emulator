#include "./../include/instruction.h"
#include "./../include/error.h"


Instruction decode(word_t* w, word_t* limit)
{
    if(w >= limit) {
        error(1, __func__, "program memory limit reached!");
    }

    
}

Opcode identify(word_t* w)
{
    // xxxx xxrd dddd rrrr
    if((*w & 0xFC00) == 0x1C00) return INS_ADC;
    if((*w & 0xFC00) == 0x0C00) return INS_ADD;
    if((*w & 0xFC00) == 0x2C00) return INS_AND;
    
    // xxxx xxxx KKdd KKKK
    if((*w & 0xFF00) == 0x9600) return INS_ADIW;
    
    // XXXX KKKK dddd KKKK
    if((*w & 0xF000) == 0x7000) return INS_ANDI;
    
    return INS_ERROR;
}
