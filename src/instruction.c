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
    if((*w & 0xFFFF) == 0x9509) return INS_ICALL;
    if((*w & 0xFFFF) == 0x9409) return INS_IJMP;

    // xxxx xxxx xsss xxxx
    if((*w & 0xFF8F) == 0x9488) return INS_BCLR;
    if((*w & 0xFF8F) == 0x9408) return INS_BSET;

    // xxxx xxxx KKKK xxxx
    if((*w & 0xFF0F) == 0x940B) return INS_DES;

    // xxxx xxxd dddd xxxx
    if((*w & 0xFE0F) == 0x940A) return INS_DEC;

    // xxxx xxxx xddd xrrr
    if((*w & 0xFF88) == 0x0308) return INS_FMUL;
    if((*w & 0xFF88) == 0x0380) return INS_FMULS;
    if((*w & 0xFF88) == 0x0388) return INS_FMULSU;

    // xxxx xxxx AAAA Abbb
    if((*w & 0xFF00) == 0x9800) return INS_CBI;

    // xxxx xxxd dddd xxxx
    if((*w & 0xFE0F) == 0x9405) return INS_ASR;
    if((*w & 0xFE0F) == 0x9403) return INS_INC;

    // xxxx xxxk kkkk xxxx
    if((*w & 0xFE0F) == 0x9400) return INS_COM;
    if((*w & 0xFE0F) == 0x9206) return INS_LAC;
    if((*w & 0xFE0F) == 0x9205) return INS_LAS;

    // xxxx xxxk kkkk xxxk
    if((*w & 0xFE0E) == 0x940E) return INS_CALL;
    if((*w & 0xFE0E) == 0x940C) return INS_JMP;

    // xxxx xxxd dddd xbbb
    if((*w & 0xFE08) == 0xFA00) return INS_BST;

    // xxxx xxkk kkkk kxxx
    if((*w & 0xFC07) == 0xF001) return INS_BREQ;
    if((*w & 0xFC07) == 0xF005) return INS_BRHS;
    if((*w & 0xFC07) == 0xF404) return INS_BRGE;
    if((*w & 0xFC07) == 0xF405) return INS_BRHC;
    if((*w & 0xFE0F) == 0x9000) return INS_LDS;
    
    if((*w & 0xF800) == 0xA000) return INS_LDS;

    // xxxx xxxd dddd xbbb
    if((*w & 0xFC00) == 0xF400) return INS_BRBC;
    if((*w & 0xFC00) == 0xF000) return INS_BRBS;

    // xxxx xxrd dddd rrrr
    if((*w & 0xFC00) == 0x1C00) return INS_ADC;
    if((*w & 0xFC00) == 0x0C00) return INS_ADD;
    if((*w & 0xFC00) == 0x2C00) return INS_AND;
    if((*w & 0xFC00) == 0x2400) return INS_EOR;
    if((*w & 0xFC00) == 0x1400) return INS_CP;
    if((*w & 0xFC00) == 0x0400) return INS_CPC;
    if((*w & 0xFC00) == 0x1000) return INS_CPSE;

    //X
    if((*w & 0xFE0F) == 0x900C) return INS_LD;
    if((*w & 0xFE0F) == 0x900D) return INS_LD;
    if((*w & 0xFE0F) == 0x900E) return INS_LD;

    //Y
    if((*w & 0xFE0F) == 0x8008) return INS_LD;
    if((*w & 0xFE0F) == 0x9009) return INS_LD;
    if((*w & 0xFE0F) == 0x900A) return INS_LD;
    if((*w & 0xD208) == 0x8008) return INS_LD;

    //Z
    if((*w & 0xFE0F) == 0x8000) return INS_LD;
    if((*w & 0xFE0F) == 0x9001) return INS_LD;
    if((*w & 0xFE0F) == 0x9002) return INS_LD;
    if((*w & 0xD208) == 0x8000) return INS_LD;

    if((*w & 0xF000) == 0xE000) return INS_LDI;

    // xxxx xxxx KKdd KKKK
    if((*w & 0xFF00) == 0x9600) return INS_ADIW;
    
    // xxxx KKKK dddd KKKK
    if((*w & 0xF000) == 0x7000) return INS_ANDI;

    // xxxx xxxd dddd 0bbb
    if((*w & 0xFE08) == 0xF800) return INS_BLD;

    // xxxx xAAd dddd AAAA
    if((*w & 0xF800) == 0xB000) return INS_IN;

    // xxxx KKKK dddd KKKK
    if((*w & 0xF000) == 0x3000) return INS_CPI;

    return INS_ERROR;
}
