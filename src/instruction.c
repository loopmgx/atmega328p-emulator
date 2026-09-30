#include "./../include/instruction.h"
#include "./../include/error.h"


Instruction decode(word_t* w, word_t* limit)
{
    if(w >= limit) {
        error(1, __func__, "program memory limit reached!");
    }

    Instruction ins;

    ins.type = identify(w);
    decode_operands(&ins);

    return ins;
}

void decode_operands(Instruction *ins)
{

    // to do LD, LPM

    // xxxx xxrd dddd rrrr
    if(
        ins->type == INS_ADC  ||
        ins->type == INS_ADD  ||
        ins->type == INS_AND  ||
        ins->type == INS_CP   ||
        ins->type == INS_CPC  ||
        ins->type == INS_CPSE ||
        ins->type == INS_EOR

    ) {}

    // xxxx xxxx xddd xrrr
    if(
        ins->type == INS_FMUL   ||
        ins->type == INS_FMULS  ||
        ins->type == INS_FMULSU
    ) {}

    // xxxx xxxx KKdd KKKK
    if(
        ins->type == INS_ADIW
    ) {}

    // xxxx KKKK dddd KKKK
    if(
        ins->type == INS_ANDI ||
        ins->type == INS_CPI  ||
        ins->type == INS_LDI
    ) {}

    // xxxx xxxd dddd xxxx
    if(
        ins->type == INS_ASR ||
        ins->type == INS_COM ||
        ins->type == INS_DEC ||
        ins->type == INS_INC
    ) {}

    // xxxx xxxx xsss xxxx
    if(
        ins->type == INS_BCLR ||
        ins->type == INS_BSET
    ) {}

    // xxxx xxxd dddd xbbb
    if(
        ins->type == INS_BLD ||
        ins->type == INS_BST
    ) {}

    // xxxx xxkk kkkk ksss
    if(
        ins->type == INS_BRBC ||
        ins->type == INS_BRBS
    ) {}

    // xxxx xxxk kkkk xxxk . kkkk kkkk kkkk kkkk
    if(
        ins->type == INS_CALL ||
        ins->type == INS_JMP
    ) {}

    // xxxx xxxd dddd xxxx . kkkk kkkk kkkk kkkk
    if(
        ins->type == INS_LDS
    ) {}

    // xxxx xxxx AAAA Abbb
    if(
        ins->type == INS_CBI
    ) {}

    // xxxx xxxx KKKK xxxx
    if(
        ins->type == INS_DES
    ) {}



}

Opcode identify(word_t* w)
{
    // xxxx xxxx xxxx xxxx
    if((*w & 0xFFFF) == 0x9598) return INS_BREAK;
    if((*w & 0xFFFF) == 0x9509) return INS_ICALL;
    if((*w & 0xFFFF) == 0x9409) return INS_IJMP;
    if((*w & 0xFFFF) == 0x95C8) return INS_LPM;
    if((*w & 0xFFFF) == 0x0000) return INS_NOP;
    if((*w & 0xFFFF) == 0x9508) return INS_RET;
    if((*w & 0xFFFF) == 0x9518) return INS_RETI;
    if((*w & 0xFFFF) == 0x9588) return INS_SLEEP;
    if((*w & 0xFFFF) == 0x95E8) return INS_SPM;
    if((*w & 0xFFFF) == 0x95A8) return INS_WDR;

    // xxxx xxxx xsss xxxx
    if((*w & 0xFF8F) == 0x9488) return INS_BCLR;
    if((*w & 0xFF8F) == 0x9408) return INS_BSET;

    // xxxx xxxx KKKK xxxx
    if((*w & 0xFF0F) == 0x940B) return INS_DES;

    // xxxx xxxd dddd xxxx
    if((*w & 0xFE0F) == 0x940A) return INS_DEC;
    if((*w & 0xFE0F) == 0x9004) return INS_LPM;
    if((*w & 0xFE0F) == 0x9005) return INS_LPM;

    // xxxx xxxx xddd xrrr
    if((*w & 0xFF88) == 0x0308) return INS_FMUL;
    if((*w & 0xFF88) == 0x0380) return INS_FMULS;
    if((*w & 0xFF88) == 0x0388) return INS_FMULSU;
    if((*w & 0xFF88) == 0x0300) return INS_MULSU;

    // xxxx xxxx AAAA Abbb
    if((*w & 0xFF00) == 0x9800) return INS_CBI;
    if((*w & 0xFF00) == 0x0100) return INS_MOVW;
    if((*w & 0xFF00) == 0x0200) return INS_MULS;
    if((*w & 0xFF00) == 0x9A00) return INS_SBI;
    if((*w & 0xFF00) == 0x9900) return INS_SBIC;
    if((*w & 0xFF00) == 0x9B00) return INS_SBIS;
    if((*w & 0xFF00) == 0x9700) return INS_SBIW;

    // xxxx xxxd dddd xxxx
    if((*w & 0xFE0F) == 0x9405) return INS_ASR;
    if((*w & 0xFE0F) == 0x9403) return INS_INC;
    if((*w & 0xFE0F) == 0x9401) return INS_NEG;
    if((*w & 0xFE0F) == 0x920C) return INS_ST;
    if((*w & 0xFE0F) == 0x920D) return INS_ST;
    if((*w & 0xFE0F) == 0x920E) return INS_ST;
    if((*w & 0xFE0F) == 0x8208) return INS_ST;
    if((*w & 0xFE0F) == 0x9209) return INS_ST;
    if((*w & 0xFE0F) == 0x920A) return INS_ST;
    if((*w & 0xDDF7) == 0x8208) return INS_ST;
    if((*w & 0xFE0F) == 0x8200) return INS_ST;
    if((*w & 0xFE0F) == 0x9201) return INS_ST;
    if((*w & 0xFE0F) == 0x9202) return INS_ST;
    if((*w & 0xD208) == 0x8200) return INS_ST;
    if((*w & 0xFE0F) == 0x9200) return INS_STS;
//

    // xxxx xxxk kkkk xxxx
    if((*w & 0xFE0F) == 0x9400) return INS_COM;
    if((*w & 0xFE0F) == 0x9206) return INS_LAC;
    if((*w & 0xFE0F) == 0x9205) return INS_LAS;
    if((*w & 0xFE0F) == 0x900F) return INS_POP;
    if((*w & 0xFE0F) == 0x920F) return INS_PUSH;
    if((*w & 0xFE0F) == 0x9402) return INS_SWAP;

    // xxxx xxxk kkkk xxxk
    if((*w & 0xFE0E) == 0x940E) return INS_CALL;
    if((*w & 0xFE0E) == 0x940C) return INS_JMP;

    // xxxx xxxd dddd xbbb
    if((*w & 0xFE08) == 0xFA00) return INS_BST;
    if((*w & 0xFE08) == 0xFC00) return INS_SBRC;
    if((*w & 0xFE08) == 0xFE00) return INS_SBRS;

    
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

    if((*w & 0xFC00) == 0x2C00) return INS_MOV;

    // xxxx xxrd dddd rrrr
    if((*w & 0xFC00) == 0x1C00) return INS_ADC;
    if((*w & 0xFC00) == 0x0C00) return INS_ADD;
    if((*w & 0xFC00) == 0x2000) return INS_AND;
    if((*w & 0xFC00) == 0x2400) return INS_EOR;
    if((*w & 0xFC00) == 0x1400) return INS_CP;
    if((*w & 0xFC00) == 0x0400) return INS_CPC;
    if((*w & 0xFC00) == 0x1000) return INS_CPSE;
    if((*w & 0xFC00) == 0x9C00) return INS_MUL;
    if((*w & 0xFC00) == 0x2800) return INS_OR;
    if((*w & 0xFC00) == 0x0800) return INS_SBC;
    if((*w & 0xFC00) == 0x1800) return INS_SUB;
    
    //X
    if((*w & 0xFE0F) == 0x900C) return INS_LD;
    if((*w & 0xFE0F) == 0x900D) return INS_LD;
    if((*w & 0xFE0F) == 0x900E) return INS_LD;
    if((*w & 0xFE0F) == 0x9407) return INS_ROR;

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
    if((*w & 0xF800) == 0xB800) return INS_OUT;

    // xxxx KKKK dddd KKKK
    if((*w & 0xF000) == 0x3000) return INS_CPI;
    if((*w & 0xF000) == 0x6000) return INS_ORI;
    // if((*w & 0xF000) == 0xD000) return INS_ORI;
    if((*w & 0xF000) == 0xC000) return INS_RJMP;
    if((*w & 0xF000) == 0x4000) return INS_SBCI;
    if((*w & 0xF000) == 0x5000) return INS_SUBI;

    return INS_ERROR;
}
