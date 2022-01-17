#include "n64dd.h"

#define LANGUAGE_JP 0
#define LANGUAGE_EN 1

// i4 texture, 192*16. Error 41
extern u8 D_801D2FE0[2][192*16/2];

// I'm not completely sure about the indices
//extern const char* D_801D2EE0[2][8][4];

s32 func_801C9B70(s32);
#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9B70.s")



extern s32 gCurrentRegion;

s32 func_801C9C48(void) {
    return gCurrentRegion == 1 ? LANGUAGE_JP : LANGUAGE_EN;
}

// #pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9C74.s")
void func_801C9C74(u8* dest, u8 value, u32 count) {
    while (count--) {
        *dest++ = value;
    }
}

// "Error Number    " array
extern const char* D_801D2ED0[];

const char* func_801C9CA4(void) {
    return D_801D2ED0[func_801C9C48()];
}

// #pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9CD4.s")
void func_801C94F8(s8*, u16);
s32 func_801C9B70(s32);

// Character indices for numbers in the error code (EUC-JP)
void func_801C9CD4(s8* arg0, s32 number) {
    s32 temp_v0 = func_801C9B70(number);
    u16 character;

    if (number >= 10) {
        character = ((temp_v0 >> 4) + '£°'); // 0, 0xA380
     } else { 
         character = '¡¡'; // Space, 0xA1A1
     }

    func_801C94F8(arg0, character);
    arg0 += 2;
    func_801C94F8(arg0, ((temp_v0 & 0xF) + '£°')); // 0, 0xA380
}

// #pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9D54.s")
// Character indices for numbers in the error code (ASCII)
void func_801C9D54(s8* arg0, s32 number) {
    s32 temp_v0 = func_801C9B70(number);

    if (number >= 10) {
        *arg0 = (temp_v0 >> 4) + '0';
    } else {
        *arg0 = ' ';
    }
    arg0++;
    *arg0 = (temp_v0 & 0xF) + '0';
}

// #pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9DB8.s")
void func_801C9A10(s32, UNK_TYPE, const char*);

void func_801C9DB8(s32 arg0, s32 errorNum) {
    const char* temp_v0 = func_801C9CA4();

    if (gCurrentRegion == LANGUAGE_EN) {
        func_801C9CD4(&temp_v0[12], errorNum);
    } else {
        func_801C9D54(&temp_v0[13], errorNum);
    }
    func_801C9A10(arg0, 0xC0, temp_v0);
}

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9E28.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9EC0.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9EF4.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9F90.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801C9FFC.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801CA030.s")

#pragma GLOBAL_ASM("oot/ne0/asm/functions/n64dd/n64dd_801C9B70/func_801CA070.s")
