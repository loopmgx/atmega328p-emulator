#include "./../include/instruction.h"
#include "./../include/error.h"
#include <stdint.h>

Instruction decode(word_t* w, word_t* limit)
{
    if(w >= limit) {
        error(1, __func__, "program memory limit reached!");
    }

    Instruction ins;

    ins.type = identify(w);
    decode_operands(&ins, w);
    return ins;
}

void decode_operands(Instruction *ins, word_t* w)
{
    if(ins->type == INS_LPM) {
        if(*w == 0x95C8) {

        }
        if((*w & 0xFE0F) == 0x9004) {
            ins->ope1.R = ((*w >> 4) & 0x1F);
            ins->ope2.XYZ.type = PTR_Z;
        }
        if((*w & 0xFE0F) == 0x9005) {
            ins->ope1.R = ((*w >> 4) & 0x1F);
            ins->ope2.XYZ.type = PTR_Z_P;
        }
    }

    if(ins->type == INS_ST) {

        // X
        if((*w & 0xFE0F) == 0x920C) {
            ins->ope1.XYZ.type = PTR_X;
        }
        if((*w & 0xFE0F) == 0x920D) {
            ins->ope1.XYZ.type = PTR_X_P;
            ins->ope1.XYZ.q = 0;
        }
        if((*w & 0xFE0F) == 0x920E) {
            ins->ope1.XYZ.type = PTR_X_M;
        }

        // Y
        if((*w & 0xFE0F) == 0x8208) {
            ins->ope1.XYZ.type = PTR_Y;
        }
        if((*w & 0xFE0F) == 0x9209) {
            ins->ope1.XYZ.type = PTR_Y_P;
            ins->ope1.XYZ.q = 0;
        }
        if((*w & 0xFE0F) == 0x920A) {
            ins->ope1.XYZ.type = PTR_Y_M;
        }
        if((*w & 0xD208) == 0x920A) {
            ins->ope1.XYZ.type = PTR_Y_Q;
            ins->ope1.XYZ.q = ((*w >> 8) & 0x20)
                            | ((*w >> 7) & 0x18)
                            | (*w & 0x07);
        }

        // Z
        if((*w & 0xFE0F) == 0x8200) {
            ins->ope1.XYZ.type = PTR_Z;
        }
        if((*w & 0xFE0F) == 0x9201) {
            ins->ope1.XYZ.type = PTR_Z_P;
            ins->ope1.XYZ.q = 0;
        }
        if((*w & 0xFE0F) == 0x9202) {
            ins->ope1.XYZ.type = PTR_Z_M;
        }
        if((*w & 0xD208) == 0x8200) {
            ins->ope1.XYZ.type = PTR_Z_Q;
            ins->ope1.XYZ.q = ((*w >> 8) & 0x20)
                            | ((*w >> 7) & 0x18)
                            | (*w & 0x07);
        }

        ins->ope2.R = (*w >> 4) & 0x1F;
    }

    // xxxx xxxd dddd xxxx | xxqx qqxd dddd xqqq
    if(ins->type == INS_LD) {
        ins->ope1.R = (*w >> 4) & 0x1F;

        // X
        if((*w & 0xFE0F) == 0x900C) {
            ins->ope2.XYZ.type = PTR_X;
        }
        if((*w & 0xFE0F) == 0x900D) {
            ins->ope2.XYZ.type = PTR_X_P;
            ins->ope2.XYZ.q = 0;
        }
        if((*w & 0xFE0F) == 0x900E) {
            ins->ope2.XYZ.type = PTR_X_M;
        }

        // Y
        if((*w & 0xFE0F) == 0x8008) {
            ins->ope2.XYZ.type = PTR_Y;
        }
        if((*w & 0xFE0F) == 0x9009) {
            ins->ope2.XYZ.type = PTR_Y_P;
            ins->ope2.XYZ.q = 0;
        }
        if((*w & 0xFE0F) == 0x900A) {
            ins->ope2.XYZ.type = PTR_Y_M;
        }
        if((*w & 0xD208) == 0x8008) {
            ins->ope2.XYZ.type = PTR_Y_Q;
            ins->ope2.XYZ.q = ((*w >> 8) & 0x20)
                            | ((*w >> 7) & 0x18)
                            | (*w & 0x07);
        }

        // Z
        if((*w & 0xFE0F) == 0x8000) {
            ins->ope2.XYZ.type = PTR_Z;
        }
        if((*w & 0xFE0F) == 0x9001) {
            ins->ope2.XYZ.type = PTR_Z_P;
            ins->ope2.XYZ.q = 0;
        }
        if((*w & 0xFE0F) == 0x9002) {
            ins->ope2.XYZ.type = PTR_Z_M;
        }
        if((*w & 0xD208) == 0x8000) {
            ins->ope2.XYZ.type = PTR_Z_Q;
            ins->ope2.XYZ.q = ((*w >> 8) & 0x20)
                            | ((*w >> 7) & 0x18)
                            | (*w & 0x07);
        }
    }

    // xxxx xxrd dddd rrrr
    if(
        ins->type == INS_ADC  ||
        ins->type == INS_ADD  ||
        ins->type == INS_AND  ||
        ins->type == INS_CP   ||
        ins->type == INS_CPC  ||
        ins->type == INS_CPSE ||
        ins->type == INS_EOR  ||
        ins->type == INS_MOV  ||
        ins->type == INS_MUL  ||
        ins->type == INS_OR   ||
        ins->type == INS_SBC  ||
        ins->type == INS_SUB

    ) {
        ins->ope1.R = (*w >> 4) & 0x1F;
        ins->ope2.R = (*w & 0x0F) | ((*w >> 5) & 0x10);
        return;
    }

    // xxxx xxxx dddd rrrr
    if(
        ins->type == INS_MOVW ||
        ins->type == INS_MULS
    ) {
        ins->ope1.R = (*w & 0x0F);
        ins->ope2.R = ((*w >> 4) & 0x0F);
    }

    // xxxx xxxx xddd xrrr
    if(
        ins->type == INS_MULSU  ||
        ins->type == INS_FMUL   ||
        ins->type == INS_FMULS  ||
        ins->type == INS_FMULSU
    ) {
        ins->ope1.R = (*w & 0x07);
        ins->ope2.K = ((*w >> 4) & 0x07);
    }

    // xxxx xxxx KKdd KKKK
    if(
        ins->type == INS_ADIW ||
        ins->type == INS_SBIW
    ) {
        ins->ope1.R = (*w & 0x30);
        ins->ope2.K = (*w & 0xCF);
    }

    // xxxx KKKK dddd KKKK
    if(
        ins->type == INS_ANDI ||
        ins->type == INS_CPI  ||
        ins->type == INS_LDI  ||
        ins->type == INS_ORI  ||
        ins->type == INS_SBCI || 
        ins->type == INS_SBR  ||
        ins->type == INS_SUBI
    ) {
        ins->ope1.R = (*w & 0xF0);
        ins->ope2.K = (*w & 0xF) | ((*w >> 4) & 0xF0);
    }

    // xxxx xxxd dddd xxxx
    if(
        ins->type == INS_ASR  ||
        ins->type == INS_COM  ||
        ins->type == INS_DEC  ||
        ins->type == INS_INC  ||
        ins->type == INS_LSR  ||
        ins->type == INS_NEG  ||
        ins->type == INS_POP  ||
        ins->type == INS_PUSH ||
        ins->type == INS_ROR  ||
        ins->type == INS_SWAP
    ) {
        ins->ope1.R = (*w >> 4) & 0x1F;
    }

    // xxxx xxxx xsss xxxx
    if(
        ins->type == INS_BCLR ||
        ins->type == INS_BSET
    ) {
        ins->ope1.s = (*w >> 4) & 0x7;
    }

    // xxxx xxxd dddd xbbb
    if(
        ins->type == INS_BLD ||
        ins->type == INS_BST
    ) {
        ins->ope1.s = (*w >> 4) & 0x1F;
        ins->ope2.b = *w & 0x7;
    }

    // xxxx xxkk kkkk ksss
    if(
        ins->type == INS_BRBC ||
        ins->type == INS_BRBS
    ) {
        ins->ope1.s = *w & 0x7;
        ins->ope1.k = (*w >> 3) & 0x7F;
    }

    // xxxx xxxk kkkk xxxk . kkkk kkkk kkkk kkkk
    if(
        ins->type == INS_CALL ||
        ins->type == INS_JMP
    ) {
        uint16_t addr =
            ((*w & 0x01F0) >> 3) |
            ((*(w + 1) & 0x3FFF) << 2);

        ins->ope1.K = addr;
    }

    // xxxx xxxd dddd xxxx . kkkk kkkk kkkk kkkk
    if(
        ins->type == INS_LDS ||
        ins->type == INS_STS
    ) {
        ins->ope1.K = *(w + 1);
        ins->ope2.R = (*w >> 4) & 0x1F;
    }

    // xxxx xxxx AAAA Abbb
    if(
        ins->type == INS_CBI  ||
        ins->type == INS_SBI  ||
        ins->type == INS_SBIC ||
        ins->type == INS_SBIS
    ) {
       ins->ope1.A = (*w >> 3) & 0x1F;
       ins->ope2.b = *w & 0x7;
    }

    // xxxx xxdd dddd dddd
    if(
        ins->type == INS_LSL ||
        ins->type == INS_ROL 
    ) {
        ins->ope1.R = (*w >> 4) & 0x1F;
    }

    // xxxx xAAr rrrr AAAA
    if(
        ins->type == INS_OUT
    ) {
        ins->ope1.A = (*w & 0xf) | ((*w >> 5) & 0x30);
        ins->ope2.R = ((*w >> 4) & 0x1F);
    }

    // xxxx kkkk kkkk kkkk
    if(
        ins->type == INS_RCALL ||
        ins->type == INS_RJMP
    ) {
        ins->ope1.K = *w & 0xFFF;
    }

    // xxxx xxxr rrrr xbbb
    if(
        ins->type == INS_SBRS
    ) {
        ins->ope1.R = (*w >> 4) & 0x1F;
        ins->ope2.b = *w & 0x7;
    }
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
