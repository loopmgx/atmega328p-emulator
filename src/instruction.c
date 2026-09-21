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
    // xxxx xxxx xxxx xxxx
    if((*w & 0xFFFF) == 0x9598) return INS_BREAK;

    if((*w & 0xFF8F) == 0x9409) return INS_BSET;

    // xxxx xxxx xsss xxxx
    if((*w & 0xFF88) == 0x9488) return INS_BCLR;

    // xxxx xxxd dddd xxxx
    if((*w & 0xFE0F) == 0x9405) return INS_ASR;

    // xxxx xxxd dddd xbbb
    if((*w & 0xFE08) == 0xFA00) return INS_BST;

    // xxxx xxkk kkkk kxxx
    if((*w & 0xFC07) == 0xF001) return INS_BREQ;
    if((*w & 0xFC07) == 0xF005) return INS_BRHS;
    if((*w & 0xFC07) == 0xF404) return INS_BRGE;
    if((*w & 0xFC07) == 0xF405) return INS_BRHC;

    // xxxx xxxd dddd xbbb
    if((*w & 0xFC00) == 0xF400) return INS_BRBC;
    if((*w & 0xFC00) == 0xF000) return INS_BRBS;

    // xxxx xxrd dddd rrrr
    if((*w & 0xFC00) == 0x1C00) return INS_ADC;
    if((*w & 0xFC00) == 0x0C00) return INS_ADD;
    if((*w & 0xFC00) == 0x2C00) return INS_AND;

    // xxxx xxxx KKdd KKKK
    if((*w & 0xFF00) == 0x9600) return INS_ADIW;
    
    // xxxx KKKK dddd KKKK
    if((*w & 0xF000) == 0x7000) return INS_ANDI;

    // xxxx xxxd dddd 0bbb
    if((*w & 0xFE08) == 0xF800) return INS_BLD;

    return INS_ERROR;
}
